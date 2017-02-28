/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 12:05:16 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:35:24 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s2[0] == '\0')
			return ((char *)s1);
		if (s1[i] == s2[j] && (i < n))
		{
			k = i;
			while (s1[k] == s2[j] && s2[j] && k < n)
			{
				k++;
				j++;
			}
			if (j == ft_strlen(s2))
				return ((char *)s1 + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
