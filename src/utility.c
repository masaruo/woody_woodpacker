#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t	write_to_fd(int dst_fd, char *src, size_t len)
{
	ssize_t	total_written = 0;
	ssize_t	bytes_written;

	while (total_written < (ssize_t) len)
	{
		bytes_written = write(dst_fd, src + total_written, len -total_written);
		if (bytes_written == -1)
			return (-1);
		total_written += bytes_written;
	}
	return (total_written);
}

void	perror_exit(int exit_code, char *msg)
{
	perror(msg);
	exit(exit_code);
}
