/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:20:49 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/26 13:16:17 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size	ft_strlcpy(char *dst, const char *src, t_size dlen)
{
	t_size	i;

	i = 0;
	if (dlen > 0)
	{
		while (i < (dlen - 1))
		{
			if (src[i])
				dst[i] = src[i];
			else
			{
				dst[i] = '\0';
				break ;
			}
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}
