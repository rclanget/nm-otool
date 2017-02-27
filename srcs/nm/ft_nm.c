#include "ft_nm.h"

#include "libft.h"

uint32_t	ft_get_magic(t_nm *s)
{
	uint32_t magic;

	magic = *(uint32_t *)s->file_addr;
	if (magic == MH_CIGAM || magic == MH_CIGAM_64 ||
		magic == FAT_CIGAM || magic == FAT_CIGAM_64)
	{
		s->swap = 1;
		magic = ft_swap_32(s, magic);
	}
	return (magic);
}

int         ft_nm(t_nm *s)
{
	uint32_t magic;

	magic = ft_get_magic(s);
	if (magic == MH_MAGIC || magic == MH_MAGIC_64)
		return (ft_get_macho(s, magic));
	else if (magic == FAT_MAGIC || magic == FAT_MAGIC_64)
		ft_printf("FAT\n");
	else if (!ft_strncmp(s->file_addr, ARMAG, SARMAG))
		ft_printf("ARCHIVE\n");
	ft_printf("Unknow format\n");
	return (EXIT_FAILURE);
}