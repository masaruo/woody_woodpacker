#include "woody.h"
#include "stub.h"
#include "libft.h"
#include "utility.h"
#include "rc4.h"//KEYSIZE

static void	create_payload(t_content const * const content, t_payload *payload,char *key)
{
	payload->executable_segment_addr = content->executable_header->p_vaddr;
	payload->executable_segment_size = content->executable_header->p_filesz;
	payload->original_entry_point = content->original_entry_point;
	payload->stub_vaddr = content->stub_vaddr;
	for (size_t i = 0; i < KEYSIZE; i++)
	{
		payload->key[i] = key[i];
	}
}

static void update_elf_header(char *head, t_content const * const content, size_t new_phdr_offset)
{
	Elf64_Ehdr			*elf_header = (Elf64_Ehdr*)head;

	elf_header->e_entry = content->stub_vaddr;
	elf_header->e_phoff = new_phdr_offset;
	elf_header->e_phnum += 1;
}

static Elf64_Phdr	*create_new_phdr(t_content *content, size_t new_phdr_offset)
{
	Elf64_Phdr	*header_table = NULL;
	Elf64_Phdr	stub_header;
	size_t		original_size = content->elf_header->e_phentsize * content->elf_header->e_phnum;
	size_t		new_size = original_size + content->elf_header->e_phentsize;

	header_table = ft_calloc(1, new_size);
	if (!header_table)
		perror_exit(1, "calloc failed while creating new product header.");

	stub_header.p_type = PT_LOAD;
	stub_header.p_flags = PF_X | PF_W | PF_R;
	stub_header.p_offset = content->stub_poffset;
	stub_header.p_vaddr = content->stub_vaddr;
	stub_header.p_paddr = content->stub_vaddr;
	stub_header.p_filesz = (new_phdr_offset + new_size) - content->stub_poffset;
	stub_header.p_memsz = (new_phdr_offset + new_size) - content->stub_poffset;
	stub_header.p_align = 0x1000;

	ft_memmove(header_table, content->head + content->elf_header->e_phoff, original_size);
	ft_memmove(&header_table[content->elf_header->e_phnum], &stub_header, sizeof(Elf64_Phdr));

	for (uint16_t i = 0; i < content->elf_header->e_phnum + 1; i++)
	{
		Elf64_Phdr	*crnt = &header_table[i];
		if (crnt->p_type == PT_PHDR)
		{
			crnt->p_offset = new_phdr_offset;
			crnt->p_vaddr = content->stub_vaddr + (new_phdr_offset - content->stub_poffset);
			crnt->p_paddr = crnt->p_vaddr;
			crnt->p_filesz = new_size;
			crnt->p_memsz = new_size;
			break;
		}
	}
	return (header_table);
}

static size_t	calc_total_packed_size(t_content *content)
{
	size_t	len = 0;
	size_t	file_len = content->stub_poffset + __obj_stub_bin_len + sizeof(t_payload);
	size_t	phdr_len = content->elf_header->e_phentsize * (content->elf_header->e_phnum + 1);
	len = file_len + phdr_len;
	return (len);
}

t_file	create_packed_file(t_content *content, char *key)
{
	size_t		new_file_total_size = calc_total_packed_size(content);
	t_file		new_file = {NULL, new_file_total_size};
	size_t		new_phdr_offset = content->stub_poffset + __obj_stub_bin_len + sizeof(t_payload);
	Elf64_Phdr	*new_phdr = create_new_phdr(content, new_phdr_offset);
	t_payload	payload;
	size_t		new_phdr_size = (content->elf_header->e_phnum + 1) * content->elf_header->e_phentsize;

	create_payload(content, &payload, key);
	new_file.head = ft_calloc(1, new_file_total_size);
	if (!new_file.head)
		perror_exit(1, "failed to create new file.");

	ft_memmove(new_file.head, content->head, content->len);
	ft_memmove(new_file.head + content->stub_poffset, __obj_stub_bin, __obj_stub_bin_len);
	ft_memmove(new_file.head + content->stub_poffset + __obj_stub_bin_len, &payload, sizeof(t_payload));
	ft_memmove(new_file.head + new_phdr_offset, new_phdr, new_phdr_size);
	free(new_phdr);
	update_elf_header(new_file.head, content, new_phdr_offset);
	return (new_file);
}
