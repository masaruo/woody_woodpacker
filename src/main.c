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
	char		*woody = NULL;
	int			orig_fd = -1;
	int			woody_fd = -1;
	off_t		len = 0;
	Elf64_Ehdr	elf_header;
	Elf64_Phdr	text_header;
	char		*decoder_stub_data = (char*) src_decoder_bin;
	size_t const		decoder_bin_len = src_decoder_bin_len;

	orig_fd = open(file_name, O_RDONLY);
	if (orig_fd == -1)
	{
		perror("");
		return (1);
	}

	woody_fd = open("woody", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (woody_fd == -1)
	{
		perror("");
		close(orig_fd);
		return (1);
	}

	int res = copy_file(woody_fd, orig_fd);
	close(orig_fd);
	if (res == -1)
	{
		perror("");
		close(woody_fd);
		return (1);
	}

	len = lseek(woody_fd, 0, SEEK_END);
	if (len == -1)
	{
		close(woody_fd);
		perror("");
		return (1);
	}

	woody = mmap(NULL, (size_t)len, PROT_READ | PROT_WRITE, MAP_SHARED, woody_fd, 0);
	close(woody_fd);
	if (woody == MAP_FAILED)
	{
		close(woody_fd);
		perror("");
		return (1);
	}

	if ((get_elf_header(woody, &elf_header, len)) == -1)
	{
		perror("");
		return (1);
	}
	if ((get_text_header(woody, &text_header, &elf_header, len)) == -1)
	{
		perror("");
		return (1);
	}

	encoder(woody, &elf_header, &text_header);

	char *newfile = injector(&woody, len, &elf_header, decoder_stub_data, decoder_bin_len);
	if (newfile == NULL)
	{
		perror("");
		free(woody);
		return(1);
	}

	int res_munmap = munmap(woody, len);//len is different. just return new woody from injector
	if (res_munmap == -1)
	{
		perror("");
		free(woody);
		return (1);
	}
	free(woody);
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
