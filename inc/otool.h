#ifndef OTOOL_H
# define OTOOL_H

#include <sys/mman.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <mach/machine.h>

# define OPTIONS	"dt"
# define OPT_D		1
# define OPT_T		2
# define USAGE		"Usage: ft_otool [OPTIONS] [FILES]\n\n" \
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
*	ft_handle_arch_32.c
*/
int						ft_handle_arch_32(t_struct *s);

/*
*	ft_handle_arch_64.c
*/
int						ft_handle_arch_64(t_struct *s);

/*
*	ft_add_segment.c
*/
int						ft_add_segment(t_struct *s, void *segment, void *section);

/*
*	ft_print_output
*/
void					ft_print_output(t_struct *s);

/*
*	ft_swap.c
*/
int64_t					ft_swap_64(t_struct *s, int64_t i);
uint32_t				ft_swap_32(t_struct *s, uint32_t val);

#endif