#include <elf.h>
#include <stdint.h>

int encoder(char *woody, Elf64_Ehdr const * const elf_header, Elf64_Phdr const * const text_header)
{
	uint64_t const	text_start_offset = text_header->p_offset;
	uint64_t const	text_segment_size = text_header->p_filesz;
	char 			*text_segment = woody + text_start_offset;
	uint64_t		i = 0;

	while (i < text_segment_size)
	{
		text_segment[i] ^= 0xff;
		i++;
	}
	return (0);
}