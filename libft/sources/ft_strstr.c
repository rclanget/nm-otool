/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:17:15 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:36:15 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	size_t	j;
	int		k;

	i = 0;
	j = 0;
	if (s2[i] == 0)
		return ((char *)s1 + i);
	while (s1[i])
	{
		if (*s2 == 0)
			return ((char *)s1);
		if (s1[i] == s2[j])
		{
			k = i;
			while (s2[j] && s1[k++] == s2[j])
				j++;
			if (j == ft_strlen(s2))
				return ((char *)s1 + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
