#include <stdio.h>//perror, printf
#include <fcntl.h>//open
#include <sys/mman.h>//mmap
#include <unistd.h>//lseek

int packer(char const * const file_name)
{
	char	*file = NULL;
	int		fd = -1;
	off_t	len = 0;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("");
		return (1);
	}

	len = lseek(fd, 0, SEEK_END);
	if (len == -1)
	{
		perror("");
		return (1);
	}

	file = mmap(NULL, (size_t)len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED)
	{
		perror("");
		return (1);
	}
	close(fd);

	//todo parse elf file
	//todo compress .text
	//todo inject decompress
	//todo modify elf header for new entry point

	int res_munmap = munmap(file, len);
	if (res_munmap == -1)
	{
		perror("");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 1)
	{
		perror("");
		return (1);
	}
	return (0);
}
