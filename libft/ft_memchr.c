/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 08:54:40 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/22 13:06:33 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, t_size n)
{
	unsigned char	*str;

	c = (unsigned char) c;
	str = (unsigned char *)s;
	while (n > 0)
	{
		if (*str == c)
			return ((void *)str);
		str++;
		n--;
	}
	return (0);
}
