/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 10:24:12 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:35:45 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strrev(char *str)
{
	int		i;
	int		j;
	char	*tmp_dest;

	i = ft_strlen(str);
	j = 0;
	tmp_dest = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	while (i > 0)
	{
		i--;
		tmp_dest[j] = str[i];
		j++;
	}
	tmp_dest[(j)] = '\0';
	return (tmp_dest);
}
