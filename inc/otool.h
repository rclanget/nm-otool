#ifndef OTOOL_H
# define OTOOL_H

#include <sys/mman.h>
#include <stdlib.h>

# define OPTIONS	"aSfHlLdt"
# define OPT_A		1
# define OPT_S		2
# define OPT_F		4
# define OPT_H		8
# define OPT_L		16
# define OPT_LL		32
# define OPT_D		64
# define OPT_T		128
# define USAGE		"Usage: ft_otool [OPTIONS] [FILES]\n\n" \
					"  -a	Display the archive header, if the file is an archive.\n" \
					"  -S	Display the contents of the `__.SYMDEF' file, if the file is an archive.\n" \
					"  -f	Display the universal headers.\n" \
					"  -H	Display the Mach header.\n" \
					"  -l	Display the load commands.\n" \
					"  -L	Display  the names and version numbers of the shared libraries that the object file uses.\n" \
					"  -d	Display the contents of the (__DATA,__data) section.\n" \
					"  -t	display text section (by default)\n"
# define MMAP_FLAG	PROT_READ, MAP_PRIVATE

typedef struct		s_struct
{
	void			*maped_file;
	unsigned int	file_size;
}					t_struct;

/*
*	ft_otool.c
*/
int					ft_otool(t_struct *s);

/*
*	ft_handle_64.c
*/
int					handle_64(t_struct *s);

/*
*	ft_option.c
*/
char				**ft_option(char **arg, int *options);

/*
*	tools.c
*/
int					ft_strlen(const char *str);
int					ft_error(const char *error);

#endif