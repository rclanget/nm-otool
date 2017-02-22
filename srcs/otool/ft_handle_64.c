#include "otool.h"

# define ARCHIVE	1
# define MACH		2
# define UNIVERSAL	3

#include <stdio.h>
#include <string.h>

void	ft_print_output_section_64(t_struct *s, t_segment *segment, char *sectname)
{
	void				*start;
	void				*p;
	void				*end;
	int					nsects;
	struct section_64	*section;
	int					i = 0;
	nsects = SEGMENT_64(segment->segment)->nsects;
	section = (struct section_64 *)((char *)SEGMENT_64(segment->segment) + sizeof(struct segment_command_64));
	while (nsects--)
	{
		if (!strcmp(section->sectname, sectname))
		{
			start = s->maped_file + section->offset;
			p = s->maped_file + section->offset;
			end = start + section->size;
			printf("Contents of (%s,%s) section\n", section->segname, section->sectname);
			printf("%016lx%c", section->addr, !strcmp(sectname, "__text") ? ' ' : '	');
			while (start < end)
			{
				printf("%02hhx ", *(char *)start);
				if (i++ == 15)
				{
					i = 0;
					printf("\n%016lx%c", section->addr + (start - p + 1), !strcmp(sectname, "__text") ? ' ' : '	');
				}
				start++;
			}
			printf("\n");
		}
		section = (struct section_64 *)((char *)section + sizeof(struct section_64));
	}
}

void	ft_print_output_header_64(t_struct *s, int type)
{
	(void)s;
	if (type == MACH)
	{
		printf("%10s %-8s %-11s %-5s %-9s%-6s%-11s %10s\n",
				"magic", "cputype", "cpusubtype", "caps", "filetype", "ncmds", "sizeofcmds", "flags");
		printf("0x%8x %-8u %11u %5s %9u%6u%11u 0x%08x\n",
				HEADER_64(s->maped_file)->magic,
				HEADER_64(s->maped_file)->cputype,
				HEADER_64(s->maped_file)->cpusubtype,
				"0x80",
				HEADER_64(s->maped_file)->filetype,
				HEADER_64(s->maped_file)->ncmds,
				HEADER_64(s->maped_file)->sizeofcmds,
				HEADER_64(s->maped_file)->flags
		);
	}
}

void	ft_print_output_64(t_struct *s)
{
	t_segment	*segments;

	segments = s->segments;
	printf("%s:\n", s->file_name);
	if (s->options & OPT_A)
		ft_print_output_header_64(s, ARCHIVE);
	if (s->options & OPT_H)
		ft_print_output_header_64(s, MACH);
	if (s->options & OPT_F)
		ft_print_output_header_64(s, UNIVERSAL);
	while (segments)
	{
		if (s->options & OPT_T && !strcmp(segments->segname, "__TEXT"))
			ft_print_output_section_64(s, segments, "__text");
		if (s->options & OPT_D && !strcmp(segments->segname, "__DATA"))
			ft_print_output_section_64(s, segments, "__data");
		segments = segments->next;
	}
}

int	ft_handle_64(t_struct *s)
{
	struct load_command	*lc;
	unsigned int		ncmds;

	ncmds = HEADER_64(s->maped_file)->ncmds;
	lc = (struct load_command *)((char *)HEADER_64(s->maped_file) + sizeof(struct mach_header_64));
	while (ncmds--)
	{
		if (lc->cmd == LC_SEGMENT_64)
			ft_add_segment(s, SEGMENT_64(lc), SEGMENT_64(lc)->segname);
		lc = (struct load_command *)((char *)lc + lc->cmdsize);
	}
	ft_print_output_64(s);
	return (0);
}