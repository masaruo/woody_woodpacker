#include <elf.h>
#include <stdint.h>

int encoder(char *file, Elf64_Ehdr const * const elf_header, Elf64_Off exec_header_offset)
{
	Elf64_Phdr		*executable_header = (Elf64_Phdr*)(file + exec_header_offset);
	uint64_t const	text_start_offset = executable_header->p_offset;
	uint64_t const	text_segment_size = executable_header->p_filesz;
	char 			*text_segment = file + text_start_offset;
	uint64_t		i = 0;

	while (i < text_segment_size)
	{
		text_segment[i] ^= 0xff;//todo update to make it harder
		i++;
	}
	return (0);
}
