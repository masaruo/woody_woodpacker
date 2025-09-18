#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t	write_to_fd(int dst_fd, char *src, size_t len)
{
	ssize_t	total_written = 0;
	ssize_t	bytes_written;
	size_t	loc = 0;

	while (total_written < len)
	{
		bytes_written = write(dst_fd, src + total_written, len -total_written);
		if (bytes_written == -1)
			return (-1);
		total_written += bytes_written;
	}
}

// int	copy_file(int dst, int src)
// {
// 	char	buf[1024];
// 	ssize_t	byte_read;

// 	while ((byte_read = read(src, buf, sizeof(buf))) > 0)
// 	{
// 		if (write_all(dst, buf, byte_read) == -1)
// 		{
// 			return (-1);
// 		}
// 	}
// 	if (byte_read == -1)
// 		return (-1);
// 	return(0);
// }

void	perror_exit(int exit_code, char *msg)
{
	perror(msg);
	exit(exit_code);
}
