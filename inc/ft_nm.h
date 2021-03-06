#ifndef NM_H
# define NM_H

#include <sys/mman.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <mach-o/ar.h>
#include <mach/machine.h>

# define OPTIONS	"dt"
# define OPT_D		1
# define OPT_T		2
# define USAGE		"Usage: ft_nm [OPTIONS] [FILES]\n\n" \
					"  -d	Display the contents of the (__DATA,__data) section.\n" \
					"  -t	display text section (by default)\n"

# define MMAP_FLAG		PROT_READ, MAP_PRIVATE

typedef enum 			e_type
{
	MACHO,
	FAT,
	ARCHIVE
}						t_type;

typedef struct 			s_nlist
{
	uint32_t			n_strx;
	char				n_type;
	uint8_t				n_sect;
	int16_t				n_desc;
	uint32_t			n_value;
	char				*name;
	struct s_nlist		*next;
}						t_nlist;

typedef struct			s_nm
{
	int					options;
	char				*file_name;
	void				*file_addr;
	size_t				file_size;
	t_type				file_type;
	int					file_subtype;
	char				swap;

	/*
	*	archive
	*/
	char				*archive_name;

	/*
	*	mach-o
	*/
	struct mach_header	*macho_header;
	uint32_t			macho_ncmds;
	struct load_command	*macho_loadcmd;
	void				*macho_symcmd;
	char				*macho_strtable;
	t_nlist				*nlists;
}						t_nm;

/*
*	ft_swap.c
*/
int64_t					ft_swap_64(t_nm *s, int64_t i);
uint32_t				ft_swap_32(t_nm *s, uint32_t val);

/*
*	ft_nm.c
*/
int						ft_nm(t_nm *s);

/*
*	ft_macho.c
*/
int						ft_get_macho(t_nm *s, uint32_t magic);

/*
*	ft_fat.c
*/
int						ft_get_fat(t_nm *s, uint32_t magic);

/*
*	ft_arch_32.c
*/
int						ft_get_arch_32(t_nm *s);

/*
*	ft_arch_64.c
*/
int						ft_get_arch_64(t_nm *s);

/*
*	ft_print_output.c
*/
void					ft_print_output(t_nm *s);

#endif