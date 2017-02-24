#include "otool.h"

int		ft_handle_fat_64(t_struct *s)
{
	struct fat_arch_64	*arch;
	unsigned int	nfat_arch;
	void			*maped_file;
	int				save_swap;

	maped_file = s->maped_file;
	save_swap = s->swap;
	nfat_arch = ft_swap_32(s, HEADER_FAT(s->maped_file)->nfat_arch);
	arch = (struct fat_arch_64 *)(maped_file + sizeof(struct fat_header));
	while (nfat_arch--)
	{
		if (ft_swap_64(s, arch->cputype) == CPU_TYPE_X86_64)
		{
			s->maped_file = (void *)((char *)maped_file + ft_swap_64(s, arch->offset));
			s->swap = 0;
			ft_otool(s);
			s->swap = save_swap;
			s->maped_file = maped_file;
			return (0);
		}
		arch++;
	}
	return (EXIT_SUCCESS);
}

int		ft_handle_fat_32(t_struct *s)
{
	struct fat_arch	*arch;
	unsigned int	nfat_arch;
	void			*maped_file;
	int				save_swap;

	maped_file = s->maped_file;
	save_swap = s->swap;
	nfat_arch = ft_swap_32(s, HEADER_FAT(s->maped_file)->nfat_arch);
	arch = (struct fat_arch *)(maped_file + sizeof(struct fat_header));
	while (nfat_arch--)
	{
		if (ft_swap_32(s, arch->cputype) == CPU_TYPE_X86_64)
		{
			s->maped_file = (void *)((char *)maped_file + ft_swap_32(s, arch->offset));
			s->swap = 0;
			ft_otool(s);
			s->swap = save_swap;
			s->maped_file = maped_file;
			return (0);
		}
		arch++;
	}
	return (EXIT_SUCCESS);
}