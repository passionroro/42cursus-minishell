/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:30:03 by rohoarau          #+#    #+#             */
/*   Updated: 2021/11/02 16:32:32 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] == c)
		{
			if (s[i + 1] != c)
				nb_words++;
			i++;
		}
		i++;
	}
	if (s[ft_strlen(s) - 1] != c)
		nb_words++;
	return (nb_words);
}

static int	ft_wordlen(const char *s, char c, int start)
{
	int	len;

	len = 0;
	while (s[start] != c && s[start])
	{
		len++;
		start++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (i < ft_countwords(s, c))
	{
		while (s[start] == c)
			start++;
		tab[i] = ft_substr(s, start, ft_wordlen(s, c, start));
		if (tab[i][0] == '\0')
		{
			tab[i] = 0;
		}
		i++;
		start += ft_wordlen(s, c, start);
	}
	tab[ft_countwords(s, c)] = NULL;
	return (tab);
}
