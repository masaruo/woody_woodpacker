#include <unistd.h>
#include <stdbool.h>

static ssize_t	write_all(int fd, char *buf, size_t count)
{
	ssize_t	total_written = 0;
	ssize_t	bytes_written;
	size_t	loc = 0;

	while (total_written < count)
	{
		bytes_written = write(fd, buf + total_written, count -total_written);
		if (bytes_written == -1)
			return (-1);
		total_written += bytes_written;
	}
}

int	copy_file(int dst, int src)
{
	char	buf[1024];
	ssize_t	byte_read;

	while ((byte_read = read(src, buf, sizeof(buf))) > 0)
	{
		if (write_all(dst, buf, byte_read) == -1)
		{
			return (-1);
		}
	}
	if (byte_read == -1)
		return (-1);
	return(0);
}