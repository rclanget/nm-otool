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
	section = segment->section;
	while (nsects--)
	{
		if (!strcmp(section->sectname, sectname))
		{
			start = s->maped_file + section->offset;
			p = s->maped_file + section->offset;
			end = start + section->size;
			printf("(%s,%s) section", section->segname, section->sectname);
			while (start < end)
			{
				printf("\n%016llx%c", section->addr + (start - p), !strcmp(sectname, "__text") ? ' ' : '	');
				i = 0;
				while (i++ < 16 && start < end)
				{
					printf("%02hhx ", *(char *)start);
					start++;
				}
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
	if (!s->archive_name)
		printf("%s:\n", s->file_name);
	else
		printf("%s(%s):\n", s->archive_name, s->file_name);
	if (s->options & OPT_A)
		ft_print_output_header_64(s, ARCHIVE);
	if (s->options & OPT_H)
		ft_print_output_header_64(s, MACH);
	if (s->options & OPT_F)
		ft_print_output_header_64(s, UNIVERSAL);
	while (segments)
	{
		if (s->options & OPT_T && !strcmp(((struct section_64 *)segments->section)->segname, "__TEXT"))
			ft_print_output_section_64(s, segments, "__text");
		if (s->options & OPT_D && !strcmp(((struct section_64 *)segments->section)->segname, "__DATA"))
			ft_print_output_section_64(s, segments, "__data");
		segments = segments->next;
	}
}

#include <unistd.h>
int	ft_handle_64(t_struct *s)
{
	struct load_command	*lc;
	unsigned int		ncmds;

	ncmds = HEADER_64(s->maped_file)->ncmds;
	lc = (struct load_command *)((char *)s->maped_file + sizeof(struct mach_header_64));
	while (ncmds--)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			struct segment_command_64 *seg64;
			seg64 = (struct segment_command_64 *)lc;
			struct section_64 *sect64;
			sect64 = (struct section_64 *)((char *)seg64 + sizeof(struct segment_command_64));

			ft_add_segment(s, seg64, sect64);
		}
		lc = (struct load_command *)((char *)lc + lc->cmdsize);
	}
	ft_print_output_64(s);
	return (0);
}