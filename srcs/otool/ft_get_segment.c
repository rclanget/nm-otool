#include "otool.h"

#include <stdio.h>
#include <string.h>

int				ft_add_segment(t_struct *s, void *segment, char *segname)
{
	t_segment *new;
	t_segment *list;

	new = (t_segment *)malloc(sizeof(t_segment));
	list = s->segments;
	new->segment = segment;
	new->segname = segname;
	new->next = NULL;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;			
	}
	else
		s->segments = new;
	return (1);
}

int				ft_get_segment(t_struct *s, struct load_command *lc, int bin_size)
{
	if (bin_size == 32 && lc->cmd == LC_SEGMENT)
		ft_add_segment(s, SEGMENT_32(lc), SEGMENT_32(lc)->segname);
	else if (bin_size == 64 && lc->cmd == LC_SEGMENT_64)
		ft_add_segment(s, SEGMENT_64(lc), SEGMENT_64(lc)->segname);
	return (1);
}