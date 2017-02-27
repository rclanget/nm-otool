#include "ft_nm.h"

#include "libft.h"

void	ft_print_output(t_nm *s)
{
	while (s->nlists)
	{
		ft_printf("-- %s\n", s->nlists->name);
		s->nlists = s->nlists->next;
	}
}