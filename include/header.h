#ifndef HEADER_H_
# define HEADER_H_
# include <elf.h>

int get_elf_header(char const * const file, Elf64_Ehdr *elf_header, __off_t len);
int	get_segment_headers(char const * const file, Elf64_Off *exec_header_offset, Elf64_Off *note_header_offset, Elf64_Ehdr const * const elf_header, __off_t len);

#endif
