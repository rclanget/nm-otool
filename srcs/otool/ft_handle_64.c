#include "otool.h"
#include "libft.h"

# define ARCHIVE	1
# define MACH		2
# define UNIVERSAL	3

#include <stdio.h>
#include <string.h>

static void	ft_print_output_section_64(t_struct *s, t_segment *segment, char *sectname)
{
	void				*start;
	void				*p;
	void				*end;
	int					nsects;
	struct section_64	*section;
	int					i = 0;

	nsects = ft_swap_64(s, SEGMENT_64(segment->segment)->nsects);
	section = segment->section;
	while (nsects--)
	{
		if (!ft_strcmp(section->sectname, sectname))
		{
			start = s->maped_file + ft_swap_64(s, section->offset);
			p = s->maped_file + ft_swap_64(s, section->offset);
			end = start + ft_swap_64(s, section->size);
			ft_printf("(%s,%s) section", section->segname, section->sectname);
			while (start < end)
			{
				ft_printf("\n%-016x%c", ft_swap_64(s, section->addr) + (start - p), !ft_strcmp(sectname, "__text") ? ' ' : '	');
				i = 0;
				while (i++ < 16 && start < end)
				{
					ft_printf("%-02x ", (uint64_t)(unsigned char)(*(char *)start));
					start++;
				}
			}
			ft_printf("\n");
		}
		section = (struct section_64 *)((char *)section + sizeof(struct section_64));
	}
}

static void	ft_print_output_64(t_struct *s)
{
	t_segment	*segments;

	segments = s->segments;
	if (!s->archive_name)
		ft_printf("%s:\n", s->file_name);
	else
		ft_printf("%s(%s):\n", s->archive_name, s->file_name);
	while (segments)
	{
		if (s->options & OPT_T && !ft_strcmp(((struct section_64 *)segments->section)->segname, "__TEXT"))
			ft_print_output_section_64(s, segments, "__text");
		if (s->options & OPT_D && !ft_strcmp(((struct section_64 *)segments->section)->segname, "__DATA"))
			ft_print_output_section_64(s, segments, "__data");
		segments = segments->next;
	}
}

#include <unistd.h>
int			ft_handle_64(t_struct *s)
{
	struct load_command	*lc;
	unsigned int		ncmds;

	ncmds = ft_swap_64(s, HEADER_64(s->maped_file)->ncmds);
	lc = (struct load_command *)((char *)s->maped_file + sizeof(struct mach_header_64));
	while (ncmds--)
	{
		if (ft_swap_64(s, lc->cmd) == LC_SEGMENT_64)
		{
			struct segment_command_64 *seg64;
			seg64 = (struct segment_command_64 *)lc;
			struct section_64 *sect64;
			sect64 = (struct section_64 *)((char *)seg64 + sizeof(struct segment_command_64));
			ft_add_segment(s, seg64, sect64);
		}
		lc = (struct load_command *)((char *)lc + ft_swap_64(s, lc->cmdsize));
	}
	ft_print_output_64(s);
	return (0);
}