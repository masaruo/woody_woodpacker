#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

#include "utility.h"
#include "libft.h"
#include "woody.h"
#include "rc4.h"

size_t const	N = 256;
size_t const	KEYSIZE = 16;

void	generate_key(char *key, size_t len)
{
	char const		charset[] = "abcdefghijklmnopqrstuvwxyz"
							"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							"0123456789";
	size_t const	charset_size = sizeof(charset) - 1;
	int				fd;

	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		perror_exit(1, "cannot generate random number");

	ssize_t	readBytes = read(fd, key, len);
	close(fd);
	if (readBytes < 0 || readBytes != len)
		perror_exit(1, "cannot read random number");

		for (int i = 0; i < len; i++)
		{
			key[i] = charset[key[i] % charset_size];
		}

	ft_putstr_fd("Key_value: ", STDOUT_FILENO);
	write(STDOUT_FILENO, key, len);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	swap(unsigned char *a, unsigned char *b)
{
	int	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	init_state(unsigned char *state, size_t len)
{
	size_t	i = 0;
	while (i < len)
	{
		state[i] = i;
		i++;
	}
}

void	ksa(char *key, unsigned char *state, size_t len)
{
	size_t	i = 0;
	size_t	j = 0;
	while (i < N)
	{
		j = (j + state[i] + key[i % len]) % N;
		swap(&state[i], &state[j]);
		i++;
	}
}

void	rc4(unsigned char *state, char *str, size_t len)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	n = 0;
	size_t	seed = 0;

	while (n < len)
	{
		i = (i + 1) % N;
		j = (j + state[i]) % N;
		swap(&state[i], &state[j]);
		seed = state[(state[i] + state[j]) % N];
		str[n] ^= seed;
		n++;
	}
}

void	encrypt(t_content *content, char *key)
{
	unsigned char	state[N];
	Elf64_Off const	offset = content->executable_header->p_offset;
	size_t const	len = content->executable_header->p_filesz;

	init_state(state, N);
	ksa(key, state, KEYSIZE);
	rc4(state, content->head + offset, len);
}
