#ifndef _ENCODE_H_
# define _ENCODE_H_
# include "woody.h"

// int encoder(char *file, Elf64_Ehdr const * const elf_header, Elf64_Off exec_header_offset);
void	encoder(t_content *content);

#endif
