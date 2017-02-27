#include "ft_nm.h"

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int	ft_munmmap_file(t_nm *s)
{
	if (munmap(s->file_addr, s->file_size) == -1)
		return (ft_error("munmap"));
	return (EXIT_SUCCESS);
}

static int	ft_map_file(t_nm *s, char *file)
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
	s->file_addr = mmap(0, info_file.st_size, MMAP_FLAG, fd, 0);
	close(fd);
	if (s->file_addr == MAP_FAILED)
		return (ft_error("mmap"));
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	t_nm		s;
	int			nb_opt;

	ft_bzero(&s, sizeof(t_nm));
	if ((nb_opt = ft_option(av, &s.options, OPTIONS, USAGE)) == -1)
		return (1);
	av = (av + (nb_opt + 1));	
	if ((ac -= nb_opt) == 1 && ++ac)
		*av = "a.out";
	while (--ac)
	{
		s.file_name = *av;
		if (ft_map_file(&s, *av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_nm(&s) == EXIT_FAILURE)
		{
			ft_munmmap_file(&s);
			return (EXIT_FAILURE);
		}
		if (ft_munmmap_file(&s) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++av;
	}
	return (EXIT_SUCCESS);
}