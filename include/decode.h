#ifndef _DECODE_H_
# define _DECODE_H_
# include <elf.h>

void	_decode(uint64_t text_segment_size, char *text_segment);
int		decoder(char *woody, Elf64_Ehdr const * const elf_header, Elf64_Phdr const * const text_header);

#endif