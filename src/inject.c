#include "woody.h"
#include "stub.h"
#include "libft.h"
#include "utility.h"
#include "rc4.h"

static t_payload	create_payload(t_content const * const content, char *key)
{
	t_payload	payload;

	payload.executable_segment_addr = content->executable_header->p_vaddr;
	payload.executable_segment_size = content->executable_header->p_memsz;
	payload.original_entry_point = content->original_entry_point;
	payload.stub_vaddr = content->last_load_header->p_vaddr + content->last_load_header->p_filesz;
	ft_memmove(payload.key, key, KEYSIZE);
	return (payload);
}

static void update_headers(char *head, t_content const * const content, size_t additional_size, size_t new_shdr_offset)
{
	Elf64_Ehdr			*elf_header = (Elf64_Ehdr*)head;
	Elf64_Phdr			*exec_header = (Elf64_Phdr*)(head + content->executable_header_offset);
	Elf64_Phdr			*last_load_header = (Elf64_Phdr*)(head + content->last_load_header_offset);
	Elf64_Addr const	new_entry_point = content->last_load_header->p_vaddr + content->last_load_header->p_filesz;//?

	elf_header->e_entry = new_entry_point;


	last_load_header->p_filesz += additional_size;

	last_load_header->p_memsz += additional_size;

	last_load_header->p_flags |= PF_X;

	exec_header->p_flags |= PF_W;

	elf_header->e_shoff = new_shdr_offset;
}

static void	copy_section_header_table(Elf64_Shdr *shdr, t_content const * const content, size_t len)
{
	Elf64_Off const	e_shoff = content->elf_header->e_shoff;
	ft_memmove(shdr, content->head + e_shoff, len);

}

t_file	create_woody(t_content *content, char *key)
{
	Elf64_Ehdr					*elf_header = content->elf_header;
	size_t const				shdr_len = elf_header->e_shentsize * elf_header->e_shnum;
	Elf64_Shdr					copied_shdr[shdr_len];
	size_t const				additional_size = __obj_stub_bin_len + sizeof(t_payload) + sizeof(copied_shdr);
	Elf64_Phdr const * const	lst = content->last_load_header;
	size_t const				last_addr = lst->p_offset + lst->p_filesz;
	size_t const				total_size = last_addr + additional_size;
	t_payload const				payload = create_payload(content, key);
	t_file						woody = {NULL, total_size};

	copy_section_header_table(copied_shdr, content, shdr_len);

	woody.head = ft_calloc(1, total_size);
	if (!woody.head)
		perror_exit(1, "malloc failed.");

	ft_memmove(woody.head, content->head, last_addr);
	ft_memmove(woody.head + last_addr, __obj_stub_bin, __obj_stub_bin_len);
	ft_memmove(woody.head + last_addr + __obj_stub_bin_len, &payload, sizeof(t_payload));

	size_t	new_shdr_offset = last_addr + __obj_stub_bin_len + sizeof(t_payload);
	ft_memmove(woody.head + new_shdr_offset, copied_shdr, sizeof(copied_shdr));

	update_headers(woody.head, content, additional_size, new_shdr_offset);

	return (woody);
}
