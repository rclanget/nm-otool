/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 09:44:25 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:26:15 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *tmp_lst;

	tmp_lst = lst;
	while (tmp_lst)
	{
		(*f)(tmp_lst);
		tmp_lst = tmp_lst->next;
	}
}
