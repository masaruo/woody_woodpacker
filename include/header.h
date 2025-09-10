#ifndef HEADER_H_
# define HEADER_H_
# include <elf.h>

int get_elf_header(char const * const file, Elf64_Ehdr *elf_header, __off_t len);
int	get_text_header(char const * const file, Elf64_Phdr *text_header, Elf64_Ehdr const * const elf_header, __off_t len);
#endif