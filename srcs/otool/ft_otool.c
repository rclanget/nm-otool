#include "otool.h"

#include <unistd.h>
#include <stdio.h>

int		ft_handle_fat_64(t_struct *s)
{
	(void)s;
	printf("FAT 64\n");
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
	nfat_arch = ft_swap_32(s, HEADER_FAT_32(maped_file)->nfat_arch);
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

int		ft_otool(t_struct *s)
{
	unsigned int magic;

	magic = *(unsigned int *)s->maped_file;
	if (magic == MH_MAGIC_64 || (magic == MH_CIGAM_64 && (s->swap = 1)))
		return (ft_handle_64(s));
	else if (magic == MH_MAGIC || (magic == MH_CIGAM && (s->swap = 1)))
		return (ft_handle_32(s));
	else if (magic == FAT_MAGIC || (magic == FAT_CIGAM && (s->swap = 1)))
		return (ft_handle_fat_32(s));
	else if (magic == FAT_MAGIC_64 || (magic == FAT_CIGAM_64  && (s->swap = 1)))
		return (ft_handle_fat_64(s));
	else
		write(2, "Unknow format\n", 15);
	return (EXIT_SUCCESS);
}