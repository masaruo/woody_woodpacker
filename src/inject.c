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
	new_header.p_vaddr = (last_addr + page_size - 1) & ~(page_size - 1);
	new_header.p_paddr = new_header.p_vaddr;
	new_header.p_align = page_size;//start on a page boundary(0x1000 bytes)

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

void	update_elf_header(char *file, Elf64_Addr decoder_vadder, Elf64_Off new_shoff)
{
	Elf64_Ehdr *elf_header = (Elf64_Ehdr*)file;
	elf_header->e_entry = decoder_vadder;
	elf_header->e_phnum += 1;
	elf_header->e_shoff = new_shoff;
}

char	*injector(char **woody, size_t woody_size, Elf64_Ehdr *elf_header, char *decoder_stub, size_t decoder_size)
{
	char			*old_file = *woody;
	char			*new_file = NULL;
	char			*new_phdr_table = NULL;
	size_t const	old_pheader_size = elf_header->e_phnum * elf_header->e_phentsize;
	size_t const	new_pheader_size = old_pheader_size + elf_header->e_phentsize;
	size_t const	new_total_size = woody_size + new_pheader_size + decoder_size;
	Elf64_Addr const	max_addr = find_last_load_address(*woody, elf_header);
	Elf64_Phdr const	decoder_header = create_decoder_header(decoder_size, woody_size, max_addr);

	new_file = ft_calloc(1, new_total_size);
	if (!new_file)
		return (NULL);
	new_phdr_table = ft_calloc(1, new_pheader_size);
	if (!new_phdr_table)
	{
		free(new_file);
		return (NULL);
	}

	ft_memmove(new_phdr_table, woody + elf_header->e_phoff, old_pheader_size);
	ft_memmove(new_phdr_table + old_pheader_size, &decoder_header, sizeof(Elf64_Phdr));

	ft_memmove(new_file, old_file, woody_size);
	ft_memmove(new_file + woody_size, decoder_stub, decoder_size);
	ft_memmove(new_file + woody_size + decoder_size, new_phdr_table, new_pheader_size);

	free(new_phdr_table);

	update_elf_header(new_file, decoder_header.p_vaddr, woody_size + decoder_size);

	// free(old_file);
	return (new_file);
}
