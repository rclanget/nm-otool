#include "otool.h"

#include <stdio.h>
#include <string.h>

static int		ft_get_segment_64(t_struct *s, struct load_command *lc)
{
	if (lc->cmd == LC_SEGMENT_64)
	{
		if (!strcmp(SEGMENT_64(lc)->segname, "__TEXT") && (s->options & OPT_T))
			printf("-> %s, %lu\n", SEGMENT_64(lc)->segname, SEGMENT_64(lc)->vmaddr);
		else if (!strcmp(SEGMENT_64(lc)->segname, "__DATA") && (s->options & OPT_D))
			printf("-> %s, %lu\n", SEGMENT_64(lc)->segname, SEGMENT_64(lc)->vmaddr);
	}
	return (0);
}

static int		ft_get_segment_32(t_struct *s, struct load_command *lc)
{
	(void)s;
	if (lc->cmd == LC_SEGMENT)
	{
		printf("-> %s, %u\n", SEGMENT_32(lc)->segname, SEGMENT_32(lc)->vmaddr);
	}
	return (0);
}

int				ft_get_segment(t_struct *s, struct load_command *lc, int bin_size)
{
	if (bin_size == 32)
		ft_get_segment_32(s, lc);
	else if (bin_size == 64)
		ft_get_segment_64(s, lc);
	return (1);
}