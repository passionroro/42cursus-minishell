/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modified.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:14:34 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/16 18:14:36 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void    check_if_even(t_split *f, char c)
{
    if (f->q == '0')
    {
        if (c == 34 || c == 39)
        {
            f->even = !f->even;
            f->q = c;
        }
    }
    else
    {
        if (c == f->q)
        {
            f->even = !f->even;
            f->q = '0';
        }
    }
}

static char	**ft_setarr(char **arr, const char *s, char c)
{
	t_split f;

	f.i = 0;
	f.r = 0;
	while (s[f.i] == c)
		f.i++;
    f.even = true;
	while (s[f.i])
	{
		f.k = 0;
        f.q = '0';
		while (!(s[f.i] == c && f.even) && s[f.i])
        {
            f.tmp[f.k++] = s[f.i++];
            check_if_even(&f, s[f.i]);
        }
		f.tmp[f.k] = '\0';
		if (f.k > 0)
		{
			arr[f.r] = ft_lastgdf(f.tmp, arr[f.r]);
			f.r++;
		}
		else
			f.i++;
	}
	arr[f.r] = 0;
	return (arr);
}

static int	ft_cnt(const char *s, char c)
{
	t_split f;

	f.i = -1;
	f.k = 0;
	while (s[++f.i])
	{
		if (s[f.i] != c)
		{
			f.k++;
			break ;
		}
	}
	f.i = 0;
    f.q = '0';
    f.even = true;
	while (s[f.i])
	{
        check_if_even(&f, s[f.i]);
		if (s[f.i] == c)
			if (f.i > 0 && s[f.i + 1] != '\0' && s[f.i + 1] != c && f.even)
				f.k++;
		f.i++;
	}
	return (f.k);
}

char	**ft_split_for_quotes(char const *s, char c)
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
