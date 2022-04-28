/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:34:24 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/26 12:01:07 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_lastgdf(char *tmp, char *arr)
{
	int		i;

	i = 0;
	while (tmp[i])
		i++;
	arr = (char *)malloc((i + 1) * sizeof(char));
	if (arr == NULL)
		return (0);
	i = 0;
	while (tmp[i])
	{
		arr[i] = tmp[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static char	**ft_setarr(char **arr, const char *s, char c)
{
	int		i;
	int		r;
	int		k;
	char	tmp[1000];

	i = 0;
	r = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		k = 0;
		while (s[i] != c && s[i])
			tmp[k++] = s[i++];
		tmp[k] = '\0';
		if (k > 0)
		{
			arr[r] = ft_lastgdf(tmp, arr[r]);
			r++;
		}
		else
			i++;
	}
	arr[r] = 0;
	return (arr);
}

static int	ft_cnt(const char *s, char c)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			k++;
			break ;
		}
	}
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
			if (i > 0 && s[i + 1] != '\0' && s[i + 1] != c)
				k++;
		i++;
	}
	return (k);
}

char	**ft_split(char const *s, char c)
{
	int		a;
	char	**arr;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		arr = malloc(1);
		arr[0] = 0;
		return (arr);
	}
	a = ft_cnt(s, c);
	arr = (char **)malloc((a + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	arr = ft_setarr(arr, s, c);
	return (arr);
}
