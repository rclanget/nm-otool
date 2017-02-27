#include "ft_nm.h"

#include "libft.h"

static int	ft_get_fat_64(t_nm *s, struct fat_arch_64 *arch, uint32_t nfat_arch)
{
	void	*save_file_addr;
	int		save_swap;

	while (nfat_arch)
	{
		if (ft_swap_32(s, arch[nfat_arch].cputype) == CPU_TYPE_X86_64)
		{
			save_file_addr = s->file_addr;
			save_swap = s->swap;
			s->file_addr = s->file_addr + ft_swap_64(s, arch[nfat_arch].offset);
			s->swap = 0;
			if (ft_nm(s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			s->file_addr = save_file_addr;
			s->swap = save_swap;
			return (EXIT_SUCCESS);
		}
		nfat_arch--;
	}
	return (EXIT_SUCCESS);
}

static int	ft_get_fat_32(t_nm *s, struct fat_arch *arch, uint32_t nfat_arch)
{
	void	*save_file_addr;
	int		save_swap;

	while (nfat_arch)
	{
		if (ft_swap_32(s, arch[nfat_arch].cputype) == CPU_TYPE_X86_64)
		{
			save_file_addr = s->file_addr;
			save_swap = s->swap;
			s->file_addr = s->file_addr + ft_swap_32(s, arch[nfat_arch].offset);
			s->swap = 0;
			if (ft_nm(s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			s->file_addr = save_file_addr;
			s->swap = save_swap;
			return (EXIT_SUCCESS);
		}
		nfat_arch--;
	}
	return (EXIT_SUCCESS);
}

int			ft_get_fat(t_nm *s, uint32_t magic)
{
	struct fat_header 	*header;
	void				*arch;
	uint32_t			nfat_arch;

	s->file_subtype = magic == FAT_MAGIC ? 32 : 64;	
	header = (struct fat_header *)s->file_addr;
	nfat_arch = ft_swap_32(s, header->nfat_arch);
	arch = (void *)((char *)header + sizeof(struct fat_header));
	if (s->file_subtype == 32)
		return (ft_get_fat_32(s, arch, nfat_arch));
	return (ft_get_fat_64(s, arch, nfat_arch));
}