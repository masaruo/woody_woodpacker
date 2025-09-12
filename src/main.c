#include <stdio.h>//perror, printf
#include <fcntl.h>//open
#include <sys/mman.h>//mmap
#include <unistd.h>//lseek
#include <sys/stat.h>//S_IREAD

#include "header.h"
#include "utility.h"

int packer(char const * const file_name)
{
	char		*packed = NULL;
	int			orig_fd = -1;
	int			packed_fd = -1;
	off_t		len = 0;
	Elf64_Ehdr	elf_header;
	Elf64_Phdr	text_header;

	orig_fd = open(file_name, O_RDONLY);
	if (orig_fd == -1)
	{
		perror("");
		return (1);
	}
	
	packed_fd = open("woody", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (packed_fd == -1)
	{
		perror("");
		close(orig_fd);
		return (1);
	}

	int res = copy_file(packed_fd, orig_fd);
	close(orig_fd);
	if (res == -1)
	{
		perror("");
		close(packed_fd);
		return (1);
	}

	len = lseek(packed_fd, 0, SEEK_END);
	if (len == -1)
	{
		close(packed_fd);
		perror("");
		return (1);
	}

	packed = mmap(NULL, (size_t)len, PROT_READ | PROT_WRITE, MAP_SHARED, packed_fd, 0);
	close(packed_fd);
	if (packed == MAP_FAILED)
	{
		close(packed_fd);
		perror("");
		return (1);
	}

	//todo parse elf file
	if ((get_elf_header(packed, &elf_header, len)) == -1)
	{
		perror("");
		return (1);
	}
	if ((get_text_header(packed, &text_header, &elf_header, len)) == -1)
	{
		perror("");
		return (1);
	}


	//todo compress .text
	//todo inject decompress
	//todo modify elf header for new entry point

	int res_munmap = munmap(packed, len);
	if (res_munmap == -1)
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
