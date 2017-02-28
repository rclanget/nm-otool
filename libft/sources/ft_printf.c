#include "libft.h"

#include <stdarg.h>


typedef struct	s_option
{
	int			left_adjust;
	int			zero_padded;
	int			width;
}				t_option;

static int		ft_nbrlen_base(unsigned long long int i, int base)
{
	return ((i < (unsigned long long int)base) ? 1 : 1 + ft_nbrlen_base(i / base, base));
}

static int		ft_putunbr_base(unsigned long long int i, int base)
{
	char				*str;
	int					ret;

	ret = 0;
	str = "0123456789abcdef";
	if (i < (unsigned long long int)base)
		write(1, str + i, 1);
	else
	{
		ret += ft_putunbr_base(i / base, base);
		write(1, str + (i % base), 1);
	}
	return (1 + ret);
}

int	ft_get_options(const char *format, t_option *opt)
{
	int		index;
	int		start;
	char	*width;

	index = 0;
	if (*(format + index) == '-' && ++index)
		opt->left_adjust = 1;
	if (*(format + index) == '0' && ++index)
		opt->zero_padded = 1;		
	start = index;
	while (ft_isdigit(*(format + index)))
		index++;
	if (start != index)
	{
		width = ft_strnew((index - start) + 1);
		ft_strncpy(width, (format + start), index - start);
		opt->width = ft_atoi(width);
		free(width);
	}
	return (index);
}

int	ft_print_string(va_list *ap, t_option *opt)
{
	char	*str;
	int		str_len;
	int		i;

	str = va_arg(*ap, char *);
	str_len = ft_strlen(str);
	i = 0;
	while (opt->left_adjust && i < (opt->width - str_len))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	write(1, str, str_len);
	while (i < (opt->width - str_len))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	return (1);
}

int	ft_print_char(va_list *ap, t_option *opt)
{
	char	c;
	int		i;

	c = (char)va_arg(*ap, int);
	i = 0;
	while (opt->left_adjust && i < (opt->width - 1))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	write(1, &c, 1);
	while (i < (opt->width - 1))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	return (1);
}

int	ft_print_signed(va_list *ap, t_option *opt, int base)
{
	long long	nbr;
	int			nbr_len;
	int			i;

	nbr = va_arg(*ap, long long);
	nbr_len = ft_nbrlen_base(nbr, base);
	i = 0;
	while (opt->left_adjust && i < (opt->width - nbr_len))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	ft_putunbr_base(nbr, base);
	while (i < (opt->width - nbr_len))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	return (1);
}


int	ft_print_unsigned(va_list *ap, t_option *opt, int base)
{
	unsigned long long	nbr;
	int			nbr_len;
	int			i;

	nbr = va_arg(*ap, unsigned long long);
	nbr_len = ft_nbrlen_base(nbr, base);
	i = 0;
	while (opt->left_adjust && i < (opt->width - nbr_len))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	ft_putunbr_base(nbr, base);
	while (i < (opt->width - nbr_len))
	{
		write(1, opt->zero_padded ? "0" : " ", 1);
		++i;
	}
	return (1);
}

int	ft_print_arg(const char *format, va_list *ap)
{
	int			ret;
	t_option	opt;

	ret = 0;
	ft_bzero(&opt, sizeof(t_option));
	if (*(format + ret))
	{
		ret += ft_get_options(format, &opt);
		if (*(format + ret) == '%')
			return (write(1, (format + ret), 1));
		if (*(format + ret) == 's')
			return (ret + ft_print_string(ap, &opt));
		if (*(format + ret) == 'c')
			return (ret + ft_print_char(ap, &opt));
		else if (*(format + ret) == 'd')
			return (ret + ft_print_signed(ap, &opt, 10));
		else if (*(format + ret) == 'u')
			return (ret + ft_print_unsigned(ap, &opt, 10));
		else if (*(format + ret) == 'x')
			return (ret + ft_print_unsigned(ap, &opt, 16));
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int			index;
	va_list		ap;

	index = 0;
	va_start(ap, format);
	while (*(format + index))
	{
		if (*(format + index) == '%')
		{
			++index;
			index += ft_print_arg(format + index, &ap);
		}
		else
		{
			write(1, format + index, 1);
			++index;
		}
	}
	va_end(ap);
	return (1);
}