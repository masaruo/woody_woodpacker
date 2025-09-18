#ifndef HEADER_H_
# define HEADER_H_
# include <elf.h>
# include <stdbool.h>
# include "woody.h"

bool	is_valid_elf_header(t_content const * const file);
int		get_segment_headers(char const * const file, Elf64_Off *exec_header_offset, Elf64_Off *note_header_offset, Elf64_Ehdr const * const elf_header, __off_t len);

#endif
