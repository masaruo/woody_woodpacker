#include <elf.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "woody.h"
#include "utility.h"
#include "libft.h"

static bool	is_valid_elf_eident(unsigned char e_ident[])
{
	if (e_ident[EI_MAG0] != ELFMAG0 || e_ident[EI_MAG1] != ELFMAG1 || e_ident[EI_MAG2] != ELFMAG2 || e_ident[EI_MAG3] != ELFMAG3)
		return (false);
	if (e_ident[EI_CLASS] != ELFCLASS64)// only 64bits
		return (false);
	if (e_ident[EI_DATA] != ELFDATA2LSB)// only little endien
		return (false);
	if (e_ident[EI_VERSION] != EV_CURRENT)
		return (false);
	return (true);
}

static bool assert_elf_header(Elf64_Ehdr const * const header)
{
	bool const	is_eident_valid = is_valid_elf_eident((unsigned char*)header->e_ident);
	if (!is_eident_valid)
		return (false);
	if (header->e_type != ET_EXEC && header->e_type != ET_DYN)// only executable
		return (false);
	if (header->e_version != EV_CURRENT)
		return (false);
	return (true);
}

static bool	is_valid_elf_header(t_content const * const content)
{
	size_t const		len = content->len;
	char const * const	file = content->head;
	Elf64_Ehdr			elf_header;

	if (len < sizeof(elf_header))
		return (false);
	ft_memmove(&elf_header, file, sizeof(Elf64_Ehdr));

	if (!assert_elf_header(&elf_header))
		return (false);
	return (true);
}

Elf64_Off	get_aligned_stub_poffset(size_t	original_len)
{
	uint64_t	page_size = 0x1000;
	size_t		new_len = (original_len + page_size - 1) & ~(page_size - 1);
	return (new_len);
}

Elf64_Addr	get_stub_vaddr(Elf64_Phdr *last_load_header)
{
	Elf64_Addr	max_vaddr_end = last_load_header->p_vaddr + last_load_header->p_memsz;
	Elf64_Addr	vaddr = 0;
	uint64_t	page_size = 0x1000;

	// vaddr = (max_vaddr_end + page_size - 1) & ~(page_size - 1);//? what are they doing?
	vaddr = (max_vaddr_end + page_size - 1) / page_size * page_size;
	return (vaddr);
}

static int	fill_content(t_content *content)
{
	content->elf_header = (Elf64_Ehdr*)content->head;
	content->original_entry_point = content->elf_header->e_entry;

	Elf64_Ehdr const	*ehdr = content->elf_header;
	Elf64_Off const		phdr_offset = ehdr->e_phoff;
	uint16_t const		phnum = ehdr->e_phnum;
	uint16_t const		phentsize = ehdr->e_phentsize;
	Elf64_Addr			max_addr = 0;

	for (size_t i = 0; i < phnum; i++)
	{
		Elf64_Phdr			*crnt;
		Elf64_Off	crnt_offset = phdr_offset + (i * phentsize);
		if (crnt_offset + phentsize > content->len)
			return (-1);

		crnt = (Elf64_Phdr*)(content->head + crnt_offset);
		if (crnt->p_type == PT_LOAD)
		{
			if (crnt->p_flags & PF_X && crnt->p_flags & PF_R)
			{
				content->executable_header = crnt;
				content->executable_header->p_flags |= PF_W;// in place decryption has to be writable
				content->executable_header_offset = crnt_offset;
			}
			Elf64_Off	end_addr = crnt->p_vaddr + crnt->p_memsz;
			if (end_addr > max_addr)
			{
				max_addr = end_addr;
				content->last_load_header = crnt;
				content->last_load_header_offset = crnt_offset;
			}
		}
	}
	if (!content->executable_header || !content->last_load_header)
		return (-1);
	else
		return (0);
}

t_content	get_original_content(char const * const file_name)
{
	t_content	original = {NULL, 0, NULL, NULL, 0, NULL, 0, 0, 0, 0};
	int fd;
	off_t	len = 0;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		perror_exit(1, "open error");
	len = lseek(fd, 0, SEEK_END);
	if (len == -1)
		perror_exit(1, "lseek eror");
	original.len = len;
		original.head = mmap(NULL, (size_t)original.len, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
	if (original.head == MAP_FAILED)
		perror_exit(1, "mmap failed");
	close(fd);
	if (!is_valid_elf_header(&original))
		perror_exit(-1, "invalid elf header");
	int res = fill_content(&original);
	if (res == -1)
		perror_exit(1, "invalid elf pheaders");

	original.stub_vaddr = get_stub_vaddr(original.last_load_header);
	original.stub_poffset = get_aligned_stub_poffset(original.len);
	return (original);
}
