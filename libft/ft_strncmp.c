/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:09:24 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/26 13:17:22 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, t_size n)
{
	unsigned const char	*ss1;
	unsigned const char	*ss2;

	ss1 = (unsigned const char *)s1;
	ss2 = (unsigned const char *)s2;
	if (n == 0)
		return (0);
	while (n > 0 && *ss1 != '\0')
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		n--;
		if (n > 0 && *ss1 + 1 != '\0')
		{
			ss1++;
			ss2++;
		}
	}
	return (*ss1 - *ss2);
}
