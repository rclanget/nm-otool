/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 17:52:52 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:36:33 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	char	*dest;
	int		i;

	i = 0;
	start = 0;
	end = ft_strlen(s);
	if (!s)
		return (NULL);
	while ((s[start] == ' ') || (s[start] == '\n') || (s[start] == '\t'))
		start++;
	while (((s[end] == ' ') || (s[end] == '\n') || (s[end] == '\t') ||
			(s[end] == '\0')) && (end > start))
		end--;
	if (!(dest = (char *)malloc(sizeof(char) * (end - start) + 1)))
		return (NULL);
	while (start < (end + 1))
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
