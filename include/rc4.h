#ifndef _RC4_H_
# define _RC4_H_
# include <stddef.h>

extern size_t const KEYSIZE;

typedef struct s_content t_content;

void	generate_key(char *key, size_t len);
void	encrypt(t_content *content, char *key);

#endif
