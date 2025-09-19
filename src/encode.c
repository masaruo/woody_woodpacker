#include "woody.h"

void encoder(t_content *content)
{
	Elf64_Off const	executable_offset = content->executable_header->p_offset;
	size_t const	executalbe_size = content->executable_header->p_memsz;
	char			*executble = content->head + executable_offset;

	for (size_t i = 0; i < executalbe_size; i++)
	{
		executble[i] ^= 0xff;//todo change to better encyption
	}
}
