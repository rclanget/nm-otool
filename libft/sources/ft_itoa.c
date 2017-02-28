/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 19:32:15 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:24:50 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countnbr(int n)
{
	int		len;
	int		positive;

	len = 1;
	positive = 0;
	if (n < 0)
	{
		n *= -1;
		positive = 1;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len + positive);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_countnbr(n);
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	dest[len] = '\0';
	if (n < 0)
	{
		n *= -1;
		dest[i++] = '-';
	}
	i = (len - 1);
	while (n > 9)
	{
		dest[i--] = ((n % 10) + 48);
		n /= 10;
	}
	if (n < 10)
		dest[i--] = (n + 48);
	return (dest);
}
