/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:03:17 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:27:06 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *tmp_s;

	tmp_s = (unsigned char *)s;
	if (s && n > 0)
	{
		while (n--)
		{
			if (*tmp_s == (unsigned char)c)
				return ((void *)tmp_s);
			tmp_s += 1;
		}
	}
	return (NULL);
}
