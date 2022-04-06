/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:48:56 by rohoarau          #+#    #+#             */
/*   Updated: 2021/10/22 16:08:34 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, t_size n)
{
	t_size			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (0);
}
