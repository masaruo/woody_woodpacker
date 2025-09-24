#include <stdio.h>//perror, printf
#include <fcntl.h>//close?
#include <sys/mman.h>//munmap
#include <unistd.h>//close
#include <stdlib.h>

#include "utility.h"
// #include "encode.h"
#include "rc4.h"

#include "woody.h"
#include "parser.h"
#include "inject.h"

int packer(char const * const file_name)
{
	t_content	data;
	t_file		woody;
	char		key[KEYSIZE];

	data = get_original_content(file_name);
	// encoder(&data);

	generate_key(key, KEYSIZE);
	encrypt(&data, key);
	woody = create_woody(&data, key);

	int res = munmap(data.head, data.len);
	if (res == -1)
	{
		//todo error
	}

	int new_fd = open("woody", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (new_fd == -1)
	{
		perror("");
		return (1);
	}

	write_to_fd(new_fd, woody.head, woody.len);
	free(woody.head);
	close(new_fd);
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
