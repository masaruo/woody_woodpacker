#ifndef _UTILITY_H_
# define _UTILITY_H_

ssize_t	write_to_fd(int dst_fd, char *src, size_t len);
void	perror_exit(int exit_code, char *msg);
#endif
