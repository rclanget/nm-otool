/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_woc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 10:06:21 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:33:11 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_woc(char *str, char *str2, char *c)
{
	char *ret_str;

	if (str[ft_strlen(str) - 1] == c[0])
		ret_str = ft_strjoin(str, str2);
	else
		ret_str = ft_strjoin(ft_strjoin(str, c), str2);
	return (ret_str);
}
