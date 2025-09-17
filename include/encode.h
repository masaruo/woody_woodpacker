#ifndef _ENCODE_H_
# define _ENCODE_H_
# include <elf.h>

int encoder(char *woody, Elf64_Ehdr const * const elf_header, Elf64_Phdr const * const text_header);

#endif
