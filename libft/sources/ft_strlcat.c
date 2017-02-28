/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:29:09 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:33:23 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t len_dest;
	size_t len_src;
	size_t i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	i = 0;
	if (n < len_dest)
		return (n + len_src);
	while (src[i] && (len_dest + i + 1) < n)
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	if (n > len_src)
		dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
