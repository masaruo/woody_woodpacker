#ifndef _INJECT_H_
# define _INJECT_H_
# include <stddef.h>
# include <elf.h>

typedef struct s_payload
{
	uint64_t	text_segment_addr;
	uint64_t	text_segment_size;
	uint64_t	original_entry_point;
	// uint64_t	key_addr;
}	t_payload;

t_payload	create_payload(char const * const orig_content, Elf64_Ehdr const * const elf_header, Elf64_Off exec_header_offset);
size_t		create_stub_injected_file(char const * const original_file, char **injected, size_t original_len, t_payload payload);
void		hijack_headers(char *orig_content, Elf64_Off note_header_offset, size_t orig_len);
#endif
