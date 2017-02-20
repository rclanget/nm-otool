#include "otool.h"
#include <stdio.h>

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

int		handle_64(t_struct *s)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	int ncmds;
	struct segment_command_64 *segment;

	header = (struct mach_header_64 *)s->maped_file;
	ncmds = header->ncmds;
	lc = (struct load_command *)((char *)header + sizeof(struct mach_header_64));
	while (ncmds--)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)lc;
			printf("-> %s, %lu\n", segment->segname, segment->vmaddr);
		}
		lc = (struct load_command *)((char *)lc + lc->cmdsize);
	}
	return (0);
}