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
	char		*orig_content = NULL;
	char		*injected = NULL;
	int			orig_fd = -1;
	int			new_fd = -1;
	off_t		len = 0;
	Elf64_Ehdr	elf_header;
	Elf64_Off	exec_header_offset;
	Elf64_Off	note_header_offset;
	t_payload	payload;

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

	orig_content = mmap(NULL, (size_t)len, PROT_WRITE | PROT_READ, MAP_PRIVATE, orig_fd, 0);
	close(orig_fd);
	if (orig_content == MAP_FAILED)
	{
		perror("");
		return (1);
	}

	if ((get_elf_header(orig_content, &elf_header, len)) == -1)
	{
		//todo munmap
		perror("");
		return (1);
	}

	if ((get_segment_headers(orig_content, &exec_header_offset, &note_header_offset, &elf_header, len)) == -1)
	{
		//todo munmap
		perror("");
		return (1);
	}

	encoder(orig_content, &elf_header, exec_header_offset);

	hijack_headers(orig_content, note_header_offset, len);
	payload = create_payload(orig_content, &elf_header, exec_header_offset);
	size_t total_len = create_stub_injected_file(orig_content, &injected, len, payload);
	int munmap_success = munmap(orig_content, len);
	if (!injected || munmap_success == -1)
	{
		free(injected);
		perror("");
		return (1);
	}

	new_fd = open("woody", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (new_fd == -1)
	{
		free (injected);
		perror("");
		return (1);
	}

	ssize_t	copy_res = write_to_fd(new_fd, injected, total_len);
	close(new_fd);
	free(injected);
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
