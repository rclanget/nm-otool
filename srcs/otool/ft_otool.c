#include "otool.h"

#include "libft.h"
#include <ar.h>
#include <mach-o/ranlib.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int		ft_is_arch_32(void *maped_file)
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
	else if (!strncmp(s->maped_file, ARMAG, SARMAG))
	{
		if (ft_is_arch_32(s->maped_file))
			return (ft_handle_arch_32(s));
		else
			return (ft_handle_arch_64(s));
	}
	else
	{
		write(2, "Unknow format\n", 15);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}