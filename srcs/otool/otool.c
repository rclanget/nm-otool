#include "otool.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MMAP_FLAG PROT_READ, MAP_PRIVATE

int ft_strlen(const char *str)
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

int	ft_otool(char *file)
{
	int			fd;
	struct stat	info_file;
	void		*maped_file;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_error("open"));
	if (fstat(fd, &info_file) == -1)
	{
		close(fd);
		return (ft_error("fstat"));
	}
	maped_file = mmap(0, info_file.st_size, MMAP_FLAG, fd, 0);
	close(fd);
	if (maped_file == MAP_FAILED)
		return (ft_error("mmap"));

	// Traitement -----
	// printf("%s\n", (char *)maped_file);
	// ----------------

	if (munmap(maped_file, info_file.st_size) == -1)
		return (ft_error("munmap"));
	return (EXIT_SUCCESS);
}

int	otool(char **files)
{
	while (files && *files)
	{
		if (ft_otool(*files) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++files;
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	int		ret;
	int		options;

	ret = EXIT_FAILURE;
	options = 0;
	if (!(av = ft_option(av, &options)))
		return (1);
	if (ac == 1)
		ret = ft_otool("a.out");
	else
		ret = otool(av);
	return (ret);
}