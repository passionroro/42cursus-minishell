/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:39:28 by rohoarau          #+#    #+#             */
/*   Updated: 2021/10/27 16:27:24 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_endchr(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	end;

	i = ft_strlen(s1) - 1;
	j = 0;
	end = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			end++;
			i--;
			j = -1;
		}
		j++;
		if (set[j] == '\0')
			return (end);
	}
	return (end);
}

static int	ft_startchr(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			start++;
			i++;
			j = -1;
		}
		j++;
		if (set[j] == '\0')
			return (start);
	}
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		setsize;
	int		start;
	int		end;
	int		i;
	char	*ptr;

	if (!s1)
		return (NULL);
	i = 0;
	start = ft_startchr(s1, set);
	end = ft_endchr(s1, set);
	setsize = ft_strlen(s1) - (start + end);
	if (setsize < 0)
		setsize = 0;
	ptr = malloc(sizeof(char) * (setsize + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < setsize)
	{
		ptr[i] = s1[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
