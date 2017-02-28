/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:57:00 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:27:26 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char *tmp_s1;
	const char *tmp_s2;

	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	if (s1 && s2 && n > 0)
	{
		while (n--)
		{
			if (*tmp_s1 != *tmp_s2)
				return ((unsigned char)*tmp_s1 - (unsigned char)*tmp_s2);
			tmp_s1++;
			tmp_s2++;
		}
	}
	return (0);
}
