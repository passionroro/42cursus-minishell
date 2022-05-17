/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:13:29 by rohoarau          #+#    #+#             */
/*   Updated: 2021/10/22 16:09:35 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, t_size len)
{
	char		*d;
	const char	*s;
	char		*lastd;
	const char	*lasts;
	t_size		i;

	d = dst;
	s = src;
	i = -1;
	if (dst == 0 && src == 0)
		return (0);
	if (d < s)
	{
		while (++i < len)
			d[i] = s[i];
	}
	else
	{
		lastd = d + (len - 1);
		lasts = s + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
