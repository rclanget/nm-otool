/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 20:42:37 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:25:52 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *lst_tmp;
	t_list *nxt_lst;

	lst_tmp = *alst;
	while (lst_tmp)
	{
		nxt_lst = lst_tmp->next;
		(*del)((lst_tmp->content), lst_tmp->content_size);
		free(lst_tmp);
		lst_tmp = nxt_lst;
	}
	*alst = NULL;
}
