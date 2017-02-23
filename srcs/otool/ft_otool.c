#include "otool.h"

#include <ar.h>

#include <unistd.h>
#include <stdio.h>

#include <string.h>
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
		return (ft_handle_arch(s));
	else
	{
		write(2, "Unknow format\n", 15);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}