#include "ft_nm.h"

#include "libft.h"
#include <unistd.h>
#include <string.h>
#include <mach-o/ar.h>
#include <mach-o/ranlib.h>

static uint32_t			get_ranlib_number(t_nm *s)
{
	struct ar_hdr	*ar;
	uint64_t 		size;
	uint64_t		nranlib;

	s->archive_name = s->file_name;
	ar = (struct ar_hdr *)(s->file_addr + SARMAG);
	size = *(uint64_t *)((char *)ar + sizeof(struct ar_hdr) + 20);
	nranlib = size / sizeof(struct ranlib_64);
	return (nranlib);
}

static struct ranlib_64	*sort_ranlib(struct ranlib_64 *rlib, uint32_t nranlib)
{
	struct ranlib_64	*rlib_sort;
	struct ranlib_64	buf;
	int					is_sorted;
	uint64_t			i;

	rlib_sort = (struct ranlib_64 *)malloc(sizeof(struct ranlib_64) * (nranlib));
	ft_bzero(rlib_sort, sizeof(struct ranlib_64) * (nranlib));
	ft_memcpy(rlib_sort, rlib, sizeof(struct ranlib_64) * nranlib);
	is_sorted = 0;
	i = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = 0;
		while ((i + 1) < nranlib)
		{
			if (rlib_sort[i].ran_off > rlib_sort[i + 1].ran_off)
			{
				ft_memcpy(&buf, &rlib_sort[i], sizeof(struct ranlib_64));
				ft_memcpy(&rlib_sort[i], &rlib_sort[i + 1], sizeof(struct ranlib_64));
				ft_memcpy(&rlib_sort[i + 1], &buf, sizeof(struct ranlib_64));
				is_sorted = 0;
			}
			i++;
		}
	}
	return (rlib_sort);
}

static struct ranlib_64	*get_ranlib_structures(t_nm *s)
{
	struct ar_hdr		*ar;
	struct ranlib_64	*rlib;
	struct ranlib_64	*rlib_sort;
	uint64_t			nranlib;

	s->archive_name = s->file_name;
	ar = (struct ar_hdr *)(s->file_addr + SARMAG);
	rlib = (struct ranlib_64 *)((char *)ar + sizeof(struct ar_hdr) + 20 + sizeof(uint64_t));
	nranlib = get_ranlib_number(s);
	rlib_sort = sort_ranlib(rlib, nranlib);
	return (rlib_sort);
}


int						ft_get_arch_64(t_nm *s)
{
	struct ranlib_64	*rlib;
	char 			*function_name;
	uint32_t 		i = 0;
	void 			*tmp;
	void 			*save_maped_file;
	uint32_t	 	nranlib;

	rlib = get_ranlib_structures(s);
	save_maped_file = s->file_addr;
	nranlib = get_ranlib_number(s);
	ft_print("Archive : %s\n", s->archive_name);
	while (i < nranlib)
	{
		function_name = (char *)s->file_addr + rlib[i].ran_off + sizeof(struct ar_hdr);
		tmp = (void *)(function_name + ft_atoi(((struct ar_hdr *)((char *)s->file_addr + rlib[i].ran_off))->ar_name + 3));
		s->file_name = function_name;
		s->file_addr = tmp;
		if (!i || (i && rlib[i].ran_off != rlib[i + 1].ran_off))
			ft_nm(s);
		s->swap = 0;
		s->file_addr = save_maped_file;
		++i;
	}
	return (EXIT_SUCCESS);
}