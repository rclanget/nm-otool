/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 15:23:11 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:23:17 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_escape(char *s)
{
	static char	buf[0x1000];
	char		*p;
	size_t		len;

	len = ft_strlen(s) - 1;
	ft_bzero((void *)buf, 0x1000);
	while (ft_isspace(*(s + len)))
		*(s + len--) = 0;
	while (ft_isspace(*s))
		s++;
	p = buf;
	while (*s++)
		if (!ft_isspace(*(s - 1)) || (ft_isspace(*(s - 1)) && !ft_isspace(*s)))
			*p++ = *(s - 1);
	return (buf);
}
