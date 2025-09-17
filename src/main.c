#include <stdio.h>//perror, printf
#include <fcntl.h>//open
#include <sys/mman.h>//mmap
#include <unistd.h>//lseek
#include <sys/stat.h>//S_IREAD
#include <stdlib.h>//free

#include "header.h"
#include "utility.h"
#include "encode.h"
#include "decoder.h"
#include "inject.h"

int packer(char const * const file_name)
{
	char		*content = NULL;
	int			orig_fd = -1;
	int			new_fd = -1;
	off_t		len = 0;
	Elf64_Ehdr	elf_header;
	Elf64_Phdr	text_header;
	char		*decoder_stub_data = (char*) decode_asm;
	size_t const		decoder_bin_len = decode_asm_len;

	orig_fd = open(file_name, O_RDONLY);
	if (orig_fd == -1)
	{
		perror("");
		return (1);
	}

	len = lseek(orig_fd, 0, SEEK_END);
	if (len == -1)
	{
		close(orig_fd);
		perror("");
		return (1);
	}

	content = mmap(NULL, (size_t)len, PROT_WRITE | PROT_READ, MAP_PRIVATE, orig_fd, 0);
	close(orig_fd);
	if (content == MAP_FAILED)
	{
		perror("");
		return (1);
	}

	if ((get_elf_header(content, &elf_header, len)) == -1)
	{
		perror("");
		return (1);
	}
	if ((get_text_header(content, &text_header, &elf_header, len)) == -1)
	{
		perror("");
		return (1);
	}

	encoder(content, &elf_header, &text_header);

	size_t woody_size = injector(&content, len, &elf_header, decoder_stub_data, decoder_bin_len);
	if (woody_size == 0)
	{
		perror("");
		return (1);
	}

	new_fd = open("woody", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (new_fd == -1)
	{
		perror("");
		free(content);
		return (1);
	}

	ssize_t	copy_res = write_to_fd(new_fd, content, woody_size);
	close(new_fd);
	if (copy_res == -1)
	{
		perror("");
		return (1);
	}

	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		perror("");
		return (1);
	}
	int res = packer(argv[1]);
	return (res);
}
