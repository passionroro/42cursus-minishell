/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:45:35 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/26 13:16:00 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_size	ft_strlcat(char *dst, const char *src, t_size n)
{
	int		i;
	t_size	d;
	int		a;

	i = 0;
	d = ft_cnt(dst);
	if (d > n)
		a = ft_cnt(src) + n;
	else
		a = d + ft_cnt(src);
	if (n > 0)
	{
		while (d < n - 1)
		{
			if (src[i])
				dst[d] = src[i];
			else
				break ;
			i++;
			d++;
		}
		dst[d] = '\0';
	}
	return (a);
}
