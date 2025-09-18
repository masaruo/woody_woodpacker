#include "header.h"
#include "libft.h"

// static bool	is_valid_elf_eident(unsigned char e_ident[])
// {
// 	if (e_ident[EI_MAG0] != ELFMAG0 || e_ident[EI_MAG1] != ELFMAG1 || e_ident[EI_MAG2] != ELFMAG2 || e_ident[EI_MAG3] != ELFMAG3)
// 		return (false);
// 	if (e_ident[EI_CLASS] != ELFCLASS64)// only 64bits
// 		return (false);
// 	if (e_ident[EI_DATA] != ELFDATA2LSB)// only little endien
// 		return (false);
// 	if (e_ident[EI_VERSION] != EV_CURRENT)
// 		return (false);
// 	return (true);
// }

// static bool assert_elf_header(Elf64_Ehdr const * const header)
// {
// 	bool const	is_eident_valid = is_valid_elf_eident((unsigned char*)header->e_ident);
// 	if (!is_eident_valid)
// 		return (false);
// 	if (header->e_type != ET_EXEC && header->e_type != ET_DYN)// only executable
// 		return (false);
// 	if (header->e_version != EV_CURRENT)
// 		return (false);
// 	return (true);
// }

// bool	is_valid_elf_header(t_content const * const content)
// {
// 	size_t const		len = content->len;
// 	char const * const	file = content->head;
// 	Elf64_Ehdr			elf_header;

// 	if (len < sizeof(elf_header))
// 		return (false);
// 	ft_memmove(&elf_header, file, sizeof(Elf64_Ehdr));

// 	if (!assert_elf_header(&elf_header))
// 		return (false);
// 	return (true);
// }

// int	get_exec_and_note_header(t_content *content)
// {
// 	Elf64_Ehdr const	*ehdr = content->elf_header;
// 	Elf64_Off const		phdr_offset = ehdr->e_phoff;
// 	uint16_t const		phnum = ehdr->e_phnum;
// 	uint16_t const		phentsize = ehdr->e_phentsize;
// 	bool				executable_found = false;
// 	bool				note_found = false;

// 	for (size_t i = 0; i < phnum; i++)
// 	{
// 		Elf64_Phdr	*crnt;
// 		Elf64_Off	crnt_offset = phdr_offset + (i * phentsize);
// 		if (crnt_offset + phentsize > content->len)
// 			return (-1);

// 		crnt = (Elf64_Phdr*)(content->head + crnt_offset);
// 		if (crnt->p_type == PT_LOAD && crnt->p_flags & PF_X && crnt->p_flags & PF_R)
// 		{
// 			content->executable_header = crnt;
// 			executable_found = true;
// 		}
// 		else if (crnt->p_type == PT_NOTE)
// 		{
// 			content->note_header = crnt;
// 			note_found = true;
// 		}
// 		if (!executable_found || !note_found)
// 			return (-1);
// 		else
// 			return (0);
// 	}
// }

// int	get_segment_headers(char const * const file, Elf64_Off *exec_header_offset, Elf64_Off *note_header_offset, Elf64_Ehdr const * const elf_header, __off_t len)
// {
// 	Elf64_Off const	product_header_start = elf_header->e_phoff;
// 	uint16_t const	number_of_headers = elf_header->e_phnum;
// 	uint16_t const	size_of_each_header = elf_header->e_phentsize;
// 	bool			exec_found = false;
// 	bool			note_found = false;

// 	for (size_t i = 0; i < number_of_headers; i++)
// 	{
// 		Elf64_Phdr		crnt;
// 		Elf64_Off const	offset = product_header_start + (i * size_of_each_header);
// 		if (offset + size_of_each_header > len)
// 			return (-1);
// 		ft_memmove(&crnt, file + offset, size_of_each_header);
// 		if (crnt.p_type == PT_LOAD && crnt.p_flags & PF_X && crnt.p_flags & PF_R)// PT_LOAD = ロード可能セグメント PF_X = 実行可能 PF_R = 読み取り可能
// 		{
// 			*exec_header_offset = product_header_start + (i * size_of_each_header);
// 			exec_found = true;
// 		}
// 		else if (crnt.p_type == PT_NOTE)
// 		{
// 			*note_header_offset = product_header_start + (i * size_of_each_header);
// 			note_found = true;
// 		}
// 	}

// 	if (exec_found && note_found)
// 		return (0);
// 	else
// 		return (-1);
// }
