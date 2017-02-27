#include "ft_nm.h"

#include "libft.h"
#include <mach-o/ranlib.h>
int			ft_is_arch_32(void *maped_file)
{
	char *symdef;
	struct ar_hdr	*ar;

	ar = (struct ar_hdr *)(maped_file + SARMAG);
	if (ft_atoi(ar->ar_name + 3) == 0)
		symdef = (char *)ar->ar_name + 3;
	else
		symdef = (char *)ar + sizeof(struct ar_hdr);
	if (!ft_strcmp(symdef, SYMDEF_64) || !ft_strcmp(symdef, SYMDEF_64_SORTED))
		return (0);
	return (1);
}

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
	uint32_t	magic;

	magic = ft_get_magic(s);
	if (magic == MH_MAGIC || magic == MH_MAGIC_64)
		return (ft_get_macho(s, magic));
	else if (magic == FAT_MAGIC || magic == FAT_MAGIC_64)
		return (ft_get_fat(s, magic));
	else if (!ft_strncmp(s->file_addr, ARMAG, SARMAG))
	{
		if (ft_is_arch_32(s->file_addr))
			return (ft_get_arch_32(s));
		return (ft_get_arch_64(s));
	}
	else
		ft_printf("Unknow format\n");
	return (EXIT_FAILURE);
}