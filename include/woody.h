#ifndef _WOODY_H_
# define _WOODY_H_
# include <stddef.h>
# include <stdbool.h>
# include <elf.h>

typedef struct s_content
{
	char		*head;
	size_t		len;
	Elf64_Ehdr	*elf_header;
	Elf64_Phdr	*executable_header;
	Elf64_Phdr	*note_header;
	Elf64_Addr	last_load_address;
}	t_content;

#endif
