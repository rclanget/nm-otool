#include "otool.h"

int	ft_add_segment(t_struct *s, void *segment, void *section)
{
	t_segment *list;
	t_segment *new;

	list = s->segments;
	new = (t_segment *)malloc(sizeof(t_segment));
	new->segment = segment;
	new->section = section;
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