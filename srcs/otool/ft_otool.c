#include "otool.h"

int		ft_otool(t_struct *s)
{
	unsigned int magic;

	magic = *(unsigned int *)s->maped_file;
	if (magic == MH_MAGIC_64)
		return (ft_handle_64(s));
	else if (magic == MH_MAGIC)
	{
		// printf("je suis un binaire 32 bits !\n");
		;
	}
	return (EXIT_SUCCESS);
}