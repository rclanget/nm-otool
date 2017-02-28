/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:46:20 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:33:04 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dst;
	int				l_s3;
	unsigned int	i;
	int				j;

	if (s1 != NULL && s2 != NULL)
	{
		l_s3 = ft_strlen(s1) + ft_strlen(s2);
		dst = (char *)malloc((l_s3 * sizeof(char) + 1));
		i = 0;
		j = 0;
		while (l_s3-- >= 0)
		{
			if (i < ft_strlen(s1))
				dst[i] = s1[i];
			else
				dst[i] = s2[j++];
			i++;
		}
		dst[i] = '\0';
		return (dst);
	}
	return (NULL);
}
