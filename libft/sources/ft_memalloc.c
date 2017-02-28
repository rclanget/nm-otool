/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 15:08:41 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:26:45 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *mem;
	char *str;

	if (size)
	{
		if (!(mem = malloc(sizeof(char) * size)))
			return (NULL);
		str = (char *)mem;
		while (size--)
			*str++ = 0;
		return (mem);
	}
	return (NULL);
}
