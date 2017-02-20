#include "otool.h"

int		ft_handle_64(t_struct *s)
{
	struct load_command		*lc;
	int ncmds;

	ncmds = HEADER_64(s->maped_file)->ncmds;
	lc = (struct load_command *)((char *)HEADER_64(s->maped_file) + sizeof(struct mach_header_64));
	while (ncmds--)
	{
		ft_get_segment(s, lc, 64);
		lc = (struct load_command *)((char *)lc + lc->cmdsize);
	}
	return (0);
}