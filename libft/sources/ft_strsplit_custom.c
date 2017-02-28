/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_custom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/30 20:18:40 by rclanget          #+#    #+#             */
/*   Updated: 2015/06/08 22:35:49 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_xcolums(char const *s, char c, char keep)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] && (s[i] == c))
			i++;
		if (s[i] && (s[i] != c || s[i] == keep))
		{
			a++;
			if (s[i] == keep)
				while (s[++i] != keep)
					;
			else
				while (s[i] && s[i] != c)
					i++;
		}
		i = (s[i] && s[i] == keep) ? i + 1 : i;
	}
	return (a);
}

char	**ft_strsplit_custom(char const *s, char c, char keep)
{
	char			**tab;
	unsigned int	i;
	unsigned int	y;
	unsigned int	len;

	y = 0;
	i = 0;
	tab = (char**)malloc(sizeof(char*) * ft_xcolums(s, c, keep) + 1);
	tab[ft_xcolums(s, c, keep)] = 0;
	while (s[i])
	{
		len = 0;
		i = (s[i] == c) ? i + 1 : i;
		if (s[i] == keep)
			while (s[++i] != keep)
				len++;
		else
			while (s[i] && s[i] != c && s[i++])
				len++;
		if (s[i - len])
			tab[y++] = ft_strsub(s, i - len, len);
		i = (s[i] == keep) ? i + 1 : i;
	}
	return (tab);
}
