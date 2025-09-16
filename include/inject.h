#ifndef _INJECT_H_
# define _INJECT_H_
# include <stddef.h>
# include <elf.h>

char	*injector(char **woody, size_t woody_size, Elf64_Ehdr *elf_header, char *decoder_stub, size_t decoder_size);

#endif
