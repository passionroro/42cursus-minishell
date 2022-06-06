/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:36:13 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/25 11:54:40 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, t_size len)
{
	t_size	i1;
	t_size	i2;
	t_size	r;
	t_size	t;

	i1 = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i1] && i1 < len)
	{
		r = i1;
		i2 = 0;
		t = i1;
		while (haystack[i1] == needle[i2] && i1 < len)
		{
			if (needle[i2 + 1] == '\0')
				return ((char *)haystack + r);
			i1++;
			i2++;
		}
		i1 = t;
		i1++;
	}
	return (0);
}
