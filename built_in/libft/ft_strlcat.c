/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:26:23 by rohoarau          #+#    #+#             */
/*   Updated: 2022/04/06 14:49:11 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size	ft_strlcat(char *dst, const char *src, t_size dstsize)
{
	t_size	d;
	t_size	s;
	t_size	temp;

	d = 0;
	s = 0;
	while (dst[d] && dstsize > d)
		d++;
	temp = d;
	if (dstsize == 0)
		return (temp + ft_strlen(src));
	while (src[s] && (dstsize - 1) > d)
	{
		dst[d] = src[s];
		s++;
		d++;
	}
	if (temp < dstsize)
		dst[d] = '\0';
	return (temp + ft_strlen(src));
}
