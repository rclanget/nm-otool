/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 12:03:50 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:27:37 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*strsrc;
	char	*strdest;
	size_t	i;

	i = 0;
	strsrc = (char *)src;
	strdest = (char *)dest;
	if (dest && src && n > 0)
	{
		while ((i < n))
		{
			strdest[i] = strsrc[i];
			i++;
		}
	}
	return ((void *)dest);
}
