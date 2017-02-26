#include "otool.h"
#include "libft.h"

# define ARCHIVE	1
# define MACH		2
# define UNIVERSAL	3

#include <stdio.h>
#include <string.h>

static void	ft_print_output_section_32(t_struct *s, t_segment *segment, char *sectname)
{
	void				*start;
	void				*p;
	void				*end;
	int					nsects;
	struct section		*section;
	int					i = 0;

	nsects = ft_swap_32(s, SEGMENT_32(segment->segment)->nsects);
	section = segment->section;
	while (nsects--)
	{
		if (!ft_strcmp(section->sectname, sectname))
		{
			start = s->maped_file + ft_swap_32(s, section->offset);
			p = s->maped_file + ft_swap_32(s, section->offset);
			end = start + ft_swap_32(s, section->size);
			ft_printf("(%s,%s) section", section->segname, section->sectname);
			while (start < end)
			{
				ft_printf("\n%-08x%c", ft_swap_32(s, section->addr) + (start - p), !ft_strcmp(sectname, "__text") ? ' ' : '	');
				i = 0;
				while (i++ < 16 && start < end)
				{
					ft_printf("%-02x ", (uint64_t)(unsigned char)(*(char *)start));
					start++;
				}
			}
			ft_printf("\n");
		}
		section = (struct section *)((char *)section + sizeof(struct section));
	}
}

static void	ft_print_output_32(t_struct *s)
{
	t_segment	*segments;

	segments = s->segments;
	if (!s->archive_name)
		ft_printf("%s:\n", s->file_name);
	else
		ft_printf("%s(%s):\n", s->archive_name, s->file_name);
	while (segments)
	{
		if (s->options & OPT_T && !ft_strcmp(((struct section *)segments->section)->segname, "__TEXT"))
			ft_print_output_section_32(s, segments, "__text");
		if (s->options & OPT_D && !ft_strcmp(((struct section *)segments->section)->segname, "__DATA"))
			ft_print_output_section_32(s, segments, "__data");
		segments = segments->next;
	}
}

int			ft_handle_32(t_struct *s)
{
	struct load_command	*lc;
	uint32_t			ncmds;

	ncmds = ft_swap_32(s, HEADER_32(s->maped_file)->ncmds);
	lc = (struct load_command *)((char *)HEADER_32(s->maped_file) + sizeof(struct mach_header));
	while (ncmds--)
	{
		if (ft_swap_32(s, lc->cmd) == LC_SEGMENT)
		{
			struct segment_command *seg32;
			seg32 = (struct segment_command *)lc;
			struct section *sect32;
			sect32 = (struct section *)((char *)seg32 + sizeof(struct segment_command));
			ft_add_segment(s, seg32, sect32);
		}
		lc = (struct load_command *)((char *)lc + ft_swap_32(s, lc->cmdsize));
	}
	ft_print_output_32(s);
	return (0);
}