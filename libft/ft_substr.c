/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:13:38 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/26 11:59:30 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, t_size len)
{
	char			*str;
	int				i;
	unsigned int	l;

	i = 0;
	l = 0;
	while (s[l])
		l++;
	if (start > l)
		str = (char *)malloc(1);
	else
	{
		l = start;
		while (s[l++] && len-- > 0)
			i++;
		str = (char *)malloc(sizeof(char) * (i + 1));
	}
	if (str == NULL)
		return (0);
	l = 0;
	while (i-- > 0)
		str[l++] = s[start++];
	str[l] = '\0';
	return (str);
}
