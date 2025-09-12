#include <elf.h>

void	_decode(uint64_t text_segment_size, char *text_segment);

int decoder(char *woody, Elf64_Ehdr const * const elf_header, Elf64_Phdr const * const text_header)
{
    uint64_t const	text_start_offset = text_header->p_offset;
	uint64_t const	text_segment_size = text_header->p_filesz;
	char 			*text_segment = woody + text_start_offset;
	uint64_t		i = 0;

	_decode(text_segment_size, text_segment);
    // decode(uint64t i, char *text_segment)
	// while (i < text_segment_size)
	// {
	// 	text_segment[i] ^= 0xff;
	// 	i++;
	// }
	return (0);
}