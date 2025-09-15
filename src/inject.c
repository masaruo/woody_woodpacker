#include <elf.h>
#include <stddef.h>
#include "libft.h"

Elf64_Phdr	create_decoder_header(size_t decoder_size, size_t original_file_size, Elf64_Addr last_addr)
{
	Elf64_Phdr		new_header;
	uint64_t const	page_size = 0x1000;

	new_header.p_type = PT_LOAD;
	new_header.p_flags = PF_R | PF_X;
	new_header.p_offset = original_file_size;
	new_header.p_filesz = decoder_size;
	new_header.p_memsz = decoder_size;
	new_header.p_vaddr = (last_addr + page_size - 1) & ~(page_size - 1);//?
	new_header.p_paddr = new_header.p_vaddr;//?
	new_header.p_align = page_size;//?

	return (new_header);
}

Elf64_Addr	find_last_load_address(char const * const file, Elf64_Ehdr const * const elf_header)
{
	Elf64_Phdr const * const	program_header = (Elf64_Phdr const * const)file + elf_header->e_phoff;
	Elf64_Addr					max_addr = 0;

	for (size_t i = 0; i < elf_header->e_phnum; i++)
	{
		if (program_header[i].p_type == PT_LOAD)//? why only checking PT_LOAD
		{
			Elf64_Addr const current_end_addr = program_header[i].p_vaddr + program_header[i].p_memsz;
			//? why p_vaddr and p_memsz?

			if (current_end_addr > max_addr)
			{
				max_addr = current_end_addr;
			}
		}
	}
	return (max_addr);
}

void	update_elf_header(Elf64_Ehdr *elf_header, Elf64_Addr decoder_vadder)
{
	elf_header->e_entry = decoder_vadder;
	elf_header->e_phnum += 1;
}

char	*inject_decode_stub(char *woody, size_t woody_size, char* decoder_stub, size_t decoder_size)
{
	char	*packer;

	packer = ft_calloc(1, woody_size + decoder_size);
	if (!packer)
		return (NULL);

	ft_memmove(packer, woody, woody_size);
	ft_memmove(packer + woody_size, decoder_stub, decoder_size);

	free(woody);
	return (packer);
}
