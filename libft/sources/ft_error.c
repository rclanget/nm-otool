#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

int	ft_error(const char *error)
{
	write(2, error, ft_strlen(error));
	write(2, " error\n", 7);
	return (EXIT_FAILURE);
}