#ifndef OTOOL_H
# define OTOOL_H

#include <sys/mman.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
// #include <mach-o/ar.h>
#include <mach/machine.h>

# define OPTIONS		"aSfHlLdt"
# define OPT_A			1
# define OPT_S			2
# define OPT_F			4
# define OPT_H			8
# define OPT_L			16
# define OPT_LL			32
# define OPT_D			64
# define OPT_T			128
# define USAGE			"Usage: ft_otool [OPTIONS] [FILES]\n\n" \
						"  -a	Display the archive header, if the file is an archive.\n" \
						"  -S	Display the contents of the `__.SYMDEF' file, if the file is an archive.\n" \
						"  -f	Display the universal headers.\n" \
						"  -H	Display the Mach header.\n" \
						"  -l	Display the load commands.\n" \
						"  -L	Display  the names and version numbers of the shared libraries that the object file uses.\n" \
						"  -d	Display the contents of the (__DATA,__data) section.\n" \
						"  -t	display text section (by default)\n"
# define MMAP_FLAG		PROT_READ, MAP_PRIVATE

# define HEADER_32(x)	((struct mach_header	*)(x))
# define HEADER_64(x)	((struct mach_header_64	*)(x))

# define HEADER_FAT(x) ((struct fat_header *)(x))

# define SEGMENT_32(x)	((struct segment_command *)(x))
# define SEGMENT_64(x)	((struct segment_command_64 *)(x))

typedef struct			s_segment
{
	void				*section;
	void				*segment;
	struct s_segment	*next;
}						t_segment;

typedef struct			s_struct
{
	int					options;
	char				*file_name;
	char				*archive_name;
	unsigned int		file_size;
	unsigned int		offset;
	void				*maped_file;
	char				swap;
	t_segment			*segments;
}						t_struct;

/*
*	ft_otool.c
*/
int						ft_otool(t_struct *s);

/*
*	ft_handle_32.c
*/
int						ft_handle_32(t_struct *s);

/*
*	ft_handle_64.c
*/
int						ft_handle_64(t_struct *s);

/*
*	ft_handle_fat.c
*/
int						ft_handle_fat_32(t_struct *s);
int						ft_handle_fat_64(t_struct *s);

/*
*	ft_handle_arch.c
*/
int						ft_handle_arch(t_struct *s);

/*
*	ft_add_segment.c
*/
int						ft_add_segment(t_struct *s, void *segment, void *section);

/*
*	ft_print_output
*/
void					ft_print_output(t_struct *s);

/*
*	ft_option.c
*/
int						ft_option(char **arg, int *options);

/*
*	ft_swap.c
*/
int64_t					ft_swap_64(t_struct *s, int64_t i);
uint32_t				ft_swap_32(t_struct *s, uint32_t val);

/*
*	tools.c
*/
int						ft_strlen(const char *str);
int						ft_error(const char *error);

#endif