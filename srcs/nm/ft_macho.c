#include "ft_nm.h"

#include "libft.h"

int			ft_add_nlist_64(t_nm *s, struct nlist_64 *nlist, uint32_t nsyms)
{
	t_nlist	*new;
	t_nlist	*tmp;

	if (!(new = (t_nlist *)malloc(sizeof(t_nlist))))
		return (EXIT_FAILURE);
	new->n_strx = ft_swap_32(s, nlist[nsyms].n_un.n_strx);
	new->n_type = nlist[nsyms].n_type;
	new->n_sect = nlist[nsyms].n_sect;
	new->n_value = ft_swap_64(s, nlist[nsyms].n_value);
	new->name = s->macho_strtable + new->n_strx;
	new->next = 0;
	if (s->nlists)
	{
		tmp = s->nlists;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		s->nlists = new;
	return (EXIT_SUCCESS);
}

int			ft_add_nlist_32(t_nm *s, struct nlist *nlist, uint32_t nsyms)
{
	t_nlist	*new;
	t_nlist	*tmp;

	if (!(new = (t_nlist *)malloc(sizeof(t_nlist))))
		return (EXIT_FAILURE);
	new->n_strx = ft_swap_32(s, nlist[nsyms].n_un.n_strx);
	new->n_type = nlist[nsyms].n_type;
	new->n_sect = nlist[nsyms].n_sect;
	new->n_value = ft_swap_32(s, nlist[nsyms].n_value);
	new->name = s->macho_strtable + new->n_strx;
	new->next = 0;
	if (s->nlists)
	{
		tmp = s->nlists;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		s->nlists = new;
	return (EXIT_SUCCESS);
}

int			ft_get_symcmd_info(t_nm *s)
{
	uint32_t				nsyms;
	void					*nlists;
	
	nsyms = ft_swap_32(s, ((struct symtab_command *)s->macho_symcmd)->nsyms);
	nlists = s->file_addr + ft_swap_32(s, ((struct symtab_command *)s->macho_symcmd)->symoff);
	while (nsyms)
	{
		if (s->file_subtype == 32)
		{
			if (ft_add_nlist_32(s, nlists, nsyms) ==  EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			if (ft_add_nlist_64(s, nlists, nsyms) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		nsyms--;
	}
	return (EXIT_SUCCESS);
}

int			ft_get_macho(t_nm *s, uint32_t magic)
{
	uint32_t				ncmds;
	struct load_command		*lc;

	s->file_subtype = magic == MH_MAGIC ? 32 : 64;
	s->macho_header = (struct mach_header *)s->file_addr;
	ncmds = ft_swap_32(s, s->macho_header->ncmds);
	if (s->file_subtype == 32)
		s->macho_loadcmd = (struct load_command *)(s->file_addr + sizeof(struct mach_header));
	else
		s->macho_loadcmd = (struct load_command *)(s->file_addr + sizeof(struct mach_header_64));
	lc = s->macho_loadcmd;
	while (ncmds--)
	{
		if (ft_swap_32(s, lc->cmd) == LC_SYMTAB)
		{
			s->macho_symcmd = (struct symtab_command *)lc;
			s->macho_strtable = (char *)s->file_addr + ft_swap_32(s, ((struct symtab_command *)s->macho_symcmd)->stroff);
			if (ft_get_symcmd_info(s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		lc = (struct load_command *)((char *)lc + lc->cmdsize);
	}
	return (EXIT_SUCCESS);
}