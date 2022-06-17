/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:56:06 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/11 11:12:25 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(const char *s1, const char *s2)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	while (s2[i2])
	{
		if (s2[i2] == s1[i1])
		{
			i2 = -1;
			i1++;
		}
		i2++;
	}
	return (i1);
}

static int	ft_end(const char *s1, const char *s2)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	while (s1[i1])
		i1++;
	i1--;
	while (s2[i2])
	{
		if (s1[i1] == s2[i2])
		{
			i2 = -1;
			i1--;
		}
		i2++;
	}
	return (i1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		s;
	int		e;
	int		i;

	if (!s1 || !set)
		return (NULL);
	s = ft_start(s1, set);
	e = ft_end(s1, set);
	i = 0;
	if (s > e)
	{
		e = 1;
		s = 2;
	}
	str = (char *)malloc((e - s + 2) * (sizeof(char)));
	if (str == NULL)
		return (0);
	while (s <= e)
		str[i++] = s1[s++];
	str[i] = '\0';
	free((void *)s1);
	return (str);
}
