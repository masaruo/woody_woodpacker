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
	Elf64_Off	executable_header_offset;
	Elf64_Phdr	*last_load_header;
	Elf64_Off	last_load_header_offset;
	Elf64_Addr	original_entry_point;
}	t_content;

typedef struct s_payload
{
	uint64_t	executable_segment_addr;
	uint64_t	executable_segment_size;
	uint64_t	original_entry_point;
	// uint64_t	key_addrs;
}	t_payload;

typedef struct s_file
{
	char	*head;
	size_t	len;
}	t_file;

#endif
