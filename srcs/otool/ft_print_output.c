#include "otool.h"
# define ARCHIVE	1
# define MACH		2
# define UNIVERSAL	3

#include <stdio.h>
#include <string.h>

void	ft_print_output_data(char *file_name, t_segment *s)
{
	(void)file_name;
	printf("%s, %ld\n", s->segname, SEGMENT_64(s->segment)->vmaddr);
}

void	ft_print_output_text(t_struct *s, t_segment *segment)
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
		if (!strcmp(section->sectname, "__text"))
		{
			start = s->maped_file + section->offset;
			p = s->maped_file + section->offset;
			end = start + section->size;
			printf("%s:\n", s->file_name);
			printf("Contents of (%s,%s) section\n", section->segname, section->sectname);

			printf("%016lx	", section->addr);
			while (start < end)
			{
				printf("%02hhx ", *(char *)start);
				if (i++ == 15)
				{
					i = 0;
					printf("\n%016lx	", section->addr + (start - p + 1));
				}
				start++;
			}
			printf("\n");
		}
		section = (struct section_64 *)((char *)section + sizeof(struct section_64));
	}
}

void	ft_print_output_header(t_segment *s, int type)
{
		(void)s;
		(void)type;
}

void	ft_print_output(t_struct *s)
{
	t_segment	*segments;

	segments = s->segments;
	while (segments)
	{
		if (s->options & OPT_A)
			ft_print_output_header(segments, ARCHIVE);
		if (s->options & OPT_H)
			ft_print_output_header(segments, MACH);
		if (s->options & OPT_F)
			ft_print_output_header(segments, UNIVERSAL);
		if (s->options & OPT_T && !strcmp(segments->segname, "__TEXT"))
			ft_print_output_text(s, segments);
		if (s->options & OPT_D && !strcmp(segments->segname, "__DATA"))
			ft_print_output_data(s->file_name, segments);
		segments = segments->next;
	}
}