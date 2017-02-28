#include "ft_nm.h"

#include "libft.h"

void	ft_print_output(t_nm *s)
{
	if (s->archive_name)
		ft_printf("\n%s(%s):\n", s->archive_name, s->file_name);
	while (s->nlists)
	{
		if (s->nlists->n_type && ft_strlen(s->nlists->name))
		{
			if (s->nlists->n_type == 't' || s->nlists->n_type == 'T' ||
				s->nlists->n_type == 'b' || s->nlists->n_type == 'B')
			{
				if (s->file_subtype == 32)
					ft_printf("%-08x ", s->nlists->n_value);
				else
					ft_printf("%-016x ", s->nlists->n_value);

			}
			else
				if (s->file_subtype == 32)
					ft_printf("%8c ", ' ');
				else
					ft_printf("%16c ", ' ');
			ft_printf("%c %s\n", s->nlists->n_type, s->nlists->name);
		}
		s->nlists = s->nlists->next;
	}
}