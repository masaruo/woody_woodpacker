#include "woody.h"
#include "stub.h"
#include "libft.h"
#include "utility.h"

static t_payload	create_payload(t_content const * const data)
{
	t_payload	payload;

	payload.executable_segment_addr = data->executable_header->p_vaddr;
	payload.executable_segment_size = data->executable_header->p_memsz;
	payload.original_entry_point = data->original_entry_point;
	//todo payload key
	return (payload);
}

// static void	update_headers(char *head, t_content const * const content, size_t additional_size)
// {

// 	Elf64_Ehdr			*elf_header = (Elf64_Ehdr*)head;
// 	Elf64_Phdr			*exec_header = (Elf64_Phdr*)(head + content->executable_header_offset);
// 	Elf64_Phdr			*last_load_header = (Elf64_Phdr*)(head + content->last_load_header_offset);
// 	Elf64_Addr const	new_entry_point = last_load_header->p_vaddr + last_load_header->p_memsz;

// 	elf_header->e_entry = new_entry_point;
// 	exec_header->p_flags |= PF_W;
// 	last_load_header->p_memsz += additional_size;
// 	last_load_header->p_filesz += additional_size;
// 	last_load_header->p_flags |= PF_X;
// }
#include <stdio.h> // printfのために追加

static void update_headers(char *head, t_content const * const content, size_t additional_size)
{
    Elf64_Ehdr          *elf_header = (Elf64_Ehdr*)head;
    Elf64_Phdr          *exec_header = (Elf64_Phdr*)(head + content->executable_header_offset);
    Elf64_Phdr          *last_load_header = (Elf64_Phdr*)(head + content->last_load_header_offset);
    Elf64_Addr const    new_entry_point = content->last_load_header->p_vaddr + content->last_load_header->p_memsz;

    // --- デバッグ用PRINTFを追加 ---
    printf("--- Updating Headers ---\n");
    printf("Additional size to add: 0x%zx (%zu bytes)\n", additional_size, additional_size);

    printf("Original Entry Point: 0x%lx\n", elf_header->e_entry);
    elf_header->e_entry = new_entry_point;
    printf("New Entry Point:      0x%lx\n", elf_header->e_entry);

    printf("Original LastLoad FileSiz: 0x%lx\n", last_load_header->p_filesz);
    last_load_header->p_filesz += additional_size;
    printf("New LastLoad FileSiz:      0x%lx\n", last_load_header->p_filesz);

    printf("Original LastLoad MemSiz:  0x%lx\n", last_load_header->p_memsz);
    last_load_header->p_memsz += additional_size;
    printf("New LastLoad MemSiz:       0x%lx\n", last_load_header->p_memsz);

    printf("Original LastLoad Flags: 0x%x\n", last_load_header->p_flags);
    last_load_header->p_flags |= PF_X;
    printf("New LastLoad Flags:      0x%x\n", last_load_header->p_flags);
    printf("------------------------\n");

    exec_header->p_flags |= PF_W;
}
t_file	create_woody(t_content *content)
{
	size_t const				additional_size = __obj_stub_bin_len + sizeof(t_payload);
	Elf64_Phdr const * const	lst = content->last_load_header;
	size_t const				last_addr = lst->p_offset + lst->p_filesz;
	size_t const				total_size = last_addr + additional_size;
	t_payload const				payload = create_payload(content);
	t_file						woody = {NULL, total_size};

	woody.head = ft_calloc(1, total_size);
	if (!woody.head)
		perror_exit(1, "malloc failed.");
	ft_memmove(woody.head, content->head, last_addr);
	ft_memmove(woody.head + last_addr, __obj_stub_bin, __obj_stub_bin_len);
	ft_memmove(woody.head + last_addr + __obj_stub_bin_len, &payload, sizeof(t_payload));

	update_headers(woody.head, content, additional_size);

	return (woody);
}
