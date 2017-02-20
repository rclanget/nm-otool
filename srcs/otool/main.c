#include "otool.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int	ft_munmmap_file(t_struct *s)
{
	if (munmap(s->maped_file, s->file_size) == -1)
		return (ft_error("munmap"));
	return (EXIT_SUCCESS);
}

static int	ft_map_file(t_struct *s, char *file)
{
	int			fd;
	struct stat	info_file;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_error("open"));
	if (fstat(fd, &info_file) == -1)
	{
		close(fd);
		return (ft_error("fstat"));
	}
	s->file_size = info_file.st_size;
	s->maped_file = mmap(0, info_file.st_size, MMAP_FLAG, fd, 0);
	close(fd);
	if (s->maped_file == MAP_FAILED)
		return (ft_error("mmap"));
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	int			options;
	t_struct	s;

	options = 0;
	s.maped_file = 0;
	s.file_size = 0;
	if (!(av = ft_option(av, &options)))
		return (1);
	// if (ac == 1)
		// *test = "a.out";
	while (--ac)
	{
		if (ft_map_file(&s, *av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_otool(&s) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_munmmap_file(&s) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++av;
	}
	return (EXIT_SUCCESS);
}