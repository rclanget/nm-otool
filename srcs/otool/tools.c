#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	ft_error(const char *error)
{
	write(2, "otool: ", 7);
	write(2, error, ft_strlen(error));
	write(2, " error\n", 7);
	return (EXIT_FAILURE);
}