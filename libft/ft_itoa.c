/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:42:44 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/20 14:23:34 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_mallocit(char *s)
{
	int		i;
	char	*mal;

	i = 0;
	while (s[i])
		i++;
	mal = (char *)malloc((i + 1) * sizeof(char));
	if (mal == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		mal[i] = s[i];
		i++;
	}
	mal[i] = '\0';
	return (mal);
}

static void	ft_switch(char *s, int i)
{
	char	t[13];
	int		p;

	p = 0;
	while (i >= 0)
	{
		t[p] = s[i];
		i--;
		p++;
	}
	t[p] = '\0';
	i++;
	while (t[i])
	{
		s[i] = t[i];
		i++;
	}
	s[i] = '\0';
}

static int	ft_ifneg(int *number)
{
	int	g;

	g = 0;
	if (*number < 0)
	{
		g++;
		if (*number == -2147483648)
		{
			g++;
			(*number)++;
		}
		*number = (*number) * -1;
	}
	return (g);
}

char	*ft_itoa(int n)
{
	char	str[12];
	char	*mal;
	int		i;
	int		g;

	i = 0;
	g = ft_ifneg(&n);
	while (n > 9)
	{
		str[i] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	if (g == 2)
		str[0] = '8';
	str[i] = n + 48;
	if (g > 0)
		str[++i] = '-';
	ft_switch(str, i);
	mal = ft_mallocit(str);
	return (mal);
}
