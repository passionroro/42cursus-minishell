/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:30:07 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/21 18:27:39 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *pdst, const void *psrc, unsigned long int n)
{
	char		*dst;
	const char	*src;
	t_size		i;

	dst = pdst;
	src = psrc;
	i = 0;
	if (src == NULL && dst == NULL)
		return (pdst);
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (pdst);
}
