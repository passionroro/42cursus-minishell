/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:12:59 by rohoarau          #+#    #+#             */
/*   Updated: 2022/02/14 17:57:46 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (11);
	if (nb <= 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	long	nb;

	nb = n;
	i = len(nb);
	ptr = malloc(sizeof(char) * (len(nb) + 1));
	if (!ptr)
		return (0);
	if (nb == 0)
		ptr[0] = '0';
	if (nb < 0)
	{
		ptr[0] = '-';
		nb *= -1;
	}
	ptr[i] = '\0';
	while (nb > 0)
	{
		i--;
		ptr[i] = nb % 10 + 48;
		nb /= 10;
	}
	return (ptr);
}
