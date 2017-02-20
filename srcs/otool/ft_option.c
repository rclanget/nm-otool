#include "otool.h"

#include <unistd.h>
#include <string.h>

static void	ft_usage(void)
{
	write(2, USAGE, strlen(USAGE));
}

static int	ft_option_error(char *program, char opt)
{
	write(2, program, strlen(program));
	write(2, ": invalid option -- '", 22);
	write(2, &opt, 1);
	write(2, "'\n", 2);
	write(2, "Please try << ", 14);
	write(2, program, strlen(program));
	write(2, " -h >> for more informations", 29);
	return (0);
}

static int	ft_pow(int exposant)
{
	int		i;

	i = 1;
	while (exposant--)
		i = i << 1;
	return (i);
}

static int	ft_option_activate(char **arg, int *options)
{
	char	*s;

	while (*(++*arg))
	{
		if (**arg == '-')
		{
			if (*(*arg + 1))
				++*arg;
			return (**arg);
		}
		else if (**arg == 'h')
		{
			ft_usage();
			return (**arg);
		}
		else if (!(s = strchr(OPTIONS, **arg)))
			return (**arg);
		*options |= ft_pow(s - OPTIONS);
	}
	return (0);
}

int			ft_option(char **arg, int *options)
{
	char	c;
	char	*program;
	int		nb_opt;

	program = *arg;
	nb_opt = 0;
	++arg;
	while (arg && *arg)
	{
		if (**arg == '-')
		{
			if (!*(*arg + 1) || (c = ft_option_activate(arg, options)))
			{
				if (c == '-')
					return (++nb_opt);
				if (c != 'h')
					ft_option_error(program, c);
				return (-1);
			}
			++nb_opt;
		}
		else
			break ;
		arg++;
	}
	return (nb_opt);
}