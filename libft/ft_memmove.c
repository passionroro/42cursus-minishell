/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:44:03 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/22 10:51:38 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *pdst, const void *psrc, unsigned long int n)
{
	const char	*ss;
	char		*dd;
	char		*dst;
	const char	*src;

	dst = pdst;
	src = psrc;
	if (n == 0 || (src == NULL && dst == NULL))
		return (pdst);
	if (dst < src)
		while (n--)
			*dst++ = *src++;
	else
	{
		dd = dst + (n - 1);
		ss = src + (n - 1);
		while (n--)
			*dd-- = *ss--;
	}
	return (pdst);
}
