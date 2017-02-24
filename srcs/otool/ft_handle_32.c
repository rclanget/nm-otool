#include "otool.h"

# define ARCHIVE	1
# define MACH		2
# define UNIVERSAL	3

#include <stdio.h>
#include <string.h>

void	ft_print_output_section_32(t_struct *s, t_segment *segment, char *sectname)
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
		if (!strcmp(section->sectname, sectname))
		{
			start = s->maped_file + ft_swap_32(s, section->offset);
			p = s->maped_file + ft_swap_32(s, section->offset);
			end = start + ft_swap_32(s, section->size);
			printf("(%s,%s) section", section->segname, section->sectname);
			while (start < end)
			{
				printf("\n%08lx%c", ft_swap_32(s, section->addr) + (start - p), !strcmp(sectname, "__text") ? ' ' : '	');
				i = 0;
				while (i++ < 16 && start < end)
				{
					printf("%02hhx ", *(char *)start);
					start++;
				}
			}
			printf("\n");
		}
		section = (struct section *)((char *)section + sizeof(struct section));
	}
}

void	ft_print_output_header_32(t_struct *s, int type)
{
	if (type == MACH)
	{
		printf("%10s %-8s %-11s %-5s %-9s%-6s%-11s %10s\n",
				"magic", "cputype", "cpusubtype", "caps", "filetype", "ncmds", "sizeofcmds", "flags");
		printf("0x%8x %-8u %11u %5s %9u%6u%11u 0x%08x\n",
				ft_swap_32(s, HEADER_32(s->maped_file)->magic),
				ft_swap_32(s, HEADER_32(s->maped_file)->cputype),
				ft_swap_32(s, HEADER_32(s->maped_file)->cpusubtype),
				"0x80",
				ft_swap_32(s, HEADER_32(s->maped_file)->filetype),
				ft_swap_32(s, HEADER_32(s->maped_file)->ncmds),
				ft_swap_32(s, HEADER_32(s->maped_file)->sizeofcmds),
				ft_swap_32(s, HEADER_32(s->maped_file)->flags)
		);
	}
}

void	ft_print_output_32(t_struct *s)
{
	t_segment	*segments;

	segments = s->segments;
	if (!s->archive_name)
		printf("%s:\n", s->file_name);
	else
		printf("%s(%s):\n", s->archive_name, s->file_name);
	if (s->options & OPT_A)
		ft_print_output_header_32(s, ARCHIVE);
	if (s->options & OPT_H)
		ft_print_output_header_32(s, MACH);
	if (s->options & OPT_F)
		ft_print_output_header_32(s, UNIVERSAL);
	while (segments)
	{
		if (s->options & OPT_T && !strcmp(((struct section *)segments->section)->segname, "__TEXT"))
			ft_print_output_section_32(s, segments, "__text");
		if (s->options & OPT_D && !strcmp(((struct section *)segments->section)->segname, "__DATA"))
			ft_print_output_section_32(s, segments, "__data");
		segments = segments->next;
	}
}
int	ft_handle_32(t_struct *s)
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