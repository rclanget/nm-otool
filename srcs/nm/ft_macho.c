#include "ft_nm.h"

#include "libft.h"

int	ft_sort_nlists(t_nm *s)
{
	t_nlist *nlists;
	int		is_sorted;
	uint32_t			tmp_n_strx;
	char				tmp_n_type;
	uint8_t				tmp_n_sect;
	int16_t				tmp_n_desc;
	uint32_t			tmp_n_value;
	char				*tmp_name;

	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		nlists = s->nlists;
		while (nlists && nlists->next)
		{
			if (ft_strcmp(nlists->name, nlists->next->name) > 0)
			{
				tmp_n_strx = nlists->n_strx;
				tmp_n_type = nlists->n_type;
				tmp_n_sect = nlists->n_sect;
				tmp_n_desc = nlists->n_desc;
				tmp_n_value = nlists->n_value;
				tmp_name = ft_strdup(nlists->name);

				nlists->n_strx = nlists->next->n_strx;
				nlists->n_type = nlists->next->n_type;
				nlists->n_sect = nlists->next->n_sect;
				nlists->n_desc = nlists->next->n_desc;
				nlists->n_value = nlists->next->n_value;
				nlists->name = ft_strdup(nlists->next->name);

				nlists->next->n_strx = tmp_n_strx;
				nlists->next->n_type = tmp_n_type;
				nlists->next->n_sect = tmp_n_sect;
				nlists->next->n_desc = tmp_n_desc;
				nlists->next->n_value = tmp_n_value;
				nlists->next->name = ft_strdup(tmp_name);

				is_sorted = 0;
				break ;
			}
			nlists = nlists->next;
		}
	}
	return (1);
}

static char			*section_32(t_nm *s, uint8_t n_sect)
{
	uint32_t				i;
	uint32_t				ncmds;
	struct load_command		*tmp_lc;
	struct section			*tmp_sect;

	i = 0;
	ncmds = 0;
	tmp_lc = s->macho_loadcmd;
	n_sect -= 1;
	while (ncmds < s->macho_ncmds)
	{
		if (tmp_lc->cmd == LC_SEGMENT)
		{
			tmp_sect = (struct section *)((char *)tmp_lc
				+ sizeof(struct segment_command));
			if (n_sect < i + ((struct segment_command *)tmp_lc)->nsects)
			{
				return (tmp_sect[n_sect - i].sectname);
			}
			i += ((struct segment_command *)tmp_lc)->nsects;
		}
		tmp_lc = (struct load_command *)((char *)tmp_lc + tmp_lc->cmdsize);
		++ncmds;
	}
	return (0);
}

static char			*section_64(t_nm *s, uint8_t n_sect)
{
	uint32_t				i;
	uint32_t				ncmds;
	struct load_command		*tmp_lc;
	struct section_64		*tmp_sect;

	i = 0;
	ncmds = 0;
	tmp_lc = s->macho_loadcmd;
	n_sect -= 1;
	while (ncmds < s->macho_ncmds)
	{
		if (tmp_lc->cmd == LC_SEGMENT_64)
		{
			tmp_sect = (struct section_64 *)((char *)tmp_lc
				+ sizeof(struct segment_command_64));
			if (n_sect < i + ((struct segment_command_64 *)tmp_lc)->nsects)
			{
				return (tmp_sect[n_sect - i].sectname);
			}
			i += ((struct segment_command_64 *)tmp_lc)->nsects;
		}
		tmp_lc = (struct load_command *)((char *)tmp_lc + tmp_lc->cmdsize);
		++ncmds;
	}
	return (0);
}

static char	ft_get_type(t_nm *s, uint8_t type, uint8_t n_sect, uint64_t n_value)
{
	char		ret;
	char		*name;

	ret = 0;
	if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	else if ((type & N_TYPE) == N_STAB)
		ret = '-';
	else if ((type & N_TYPE) == N_UNDF && (type & N_EXT) && n_value != 0)
		ret = 'C';
	else if ((type & N_TYPE) == N_UNDF && (type & N_TYPE) == N_PBUD)
		ret = 'u';
	else if ((type & N_TYPE) == N_UNDF)
		ret = 'U';
	else if ((type & N_TYPE) == N_ABS)
		ret = 's';
	else if ((type & N_TYPE) == N_SECT)
	{
		if ((name = (s->file_subtype == 32 ? section_32(s, n_sect) : section_64(s, n_sect))))
		{
			if (!strcmp(name, SECT_DATA))
				ret = 'D';
			else if (!strcmp(name, SECT_BSS))
				ret = 'B';
			else if (!strcmp(name, SECT_TEXT))
				ret = 'T';
			else
				ret = 'S';
		}
	}
	return ((ret && !(type & N_EXT)) ? ft_tolower(ret) : ret);
}

static int		ft_add_nlist_64(t_nm *s, struct nlist_64 *nlist, uint32_t nsyms)
{
	t_nlist	*new;
	t_nlist	*tmp;

	if (!(new = (t_nlist *)malloc(sizeof(t_nlist))))
		return (EXIT_FAILURE);
	new->n_strx = ft_swap_32(s, nlist[nsyms].n_un.n_strx);
	new->n_sect = nlist[nsyms].n_sect;
	new->n_value = ft_swap_64(s, nlist[nsyms].n_value);
	new->n_type = ft_get_type(s, nlist[nsyms].n_type, new->n_sect, new->n_value);
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

static int		ft_add_nlist_32(t_nm *s, struct nlist *nlist, uint32_t nsyms)
{
	t_nlist	*new;
	t_nlist	*tmp;

	if (!(new = (t_nlist *)malloc(sizeof(t_nlist))))
		return (EXIT_FAILURE);
	new->n_strx = ft_swap_32(s, nlist[nsyms].n_un.n_strx);
	new->n_sect = nlist[nsyms].n_sect;
	new->n_value = ft_swap_32(s, nlist[nsyms].n_value);
	new->n_type = ft_get_type(s, nlist[nsyms].n_type, new->n_sect, new->n_value);
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

int				ft_get_symcmd_info(t_nm *s)
{
	uint32_t	nsyms;
	void		*nlists;
	uint32_t	i;

	nsyms = ft_swap_32(s, ((struct symtab_command *)s->macho_symcmd)->nsyms);
	nlists = s->file_addr + 
		ft_swap_32(s, ((struct symtab_command *)s->macho_symcmd)->symoff);
	i = 0;
	while (i < nsyms)
	{
		if (s->file_subtype == 32)
		{
			if (ft_add_nlist_32(s, nlists, i) ==  EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			if (ft_add_nlist_64(s, nlists, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int				ft_get_macho(t_nm *s, uint32_t magic)
{
	uint32_t			ncmds;
	struct load_command	*lc;

	s->file_subtype = (magic == MH_MAGIC ? 32 : 64);
	s->macho_header = (struct mach_header *)s->file_addr;
	s->macho_ncmds = ft_swap_32(s, s->macho_header->ncmds);
	ncmds = s->macho_ncmds;
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
		lc = (struct load_command *)((char *)lc + ft_swap_32(s, lc->cmdsize));
	}
	ft_sort_nlists(s);
	ft_print_output(s);
	return (EXIT_SUCCESS);
}