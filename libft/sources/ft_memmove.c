/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 10:35:17 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:27:57 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*tmp_dest;
	const char	*tmp_src;

	tmp_dest = dest;
	tmp_src = src;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	tmp_dest += n - 1;
	tmp_src += n - 1;
	while (n--)
	{
		*tmp_dest-- = *tmp_src--;
	}
	return (dest);
}
