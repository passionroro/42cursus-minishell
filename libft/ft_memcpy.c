/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:22:42 by rohoarau          #+#    #+#             */
/*   Updated: 2021/10/22 16:23:07 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, t_size n)
{
	unsigned char		*d;
	const unsigned char	*s;
	t_size				i;

	d = dst;
	s = src;
	i = -1;
	if (n == 0 || (s == 0 && d == 0))
		return (dst);
	while (++i < n)
		d[i] = s[i];
	return (dst);
}
