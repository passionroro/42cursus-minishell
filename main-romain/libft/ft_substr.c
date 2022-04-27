/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:40:23 by rohoarau          #+#    #+#             */
/*   Updated: 2022/04/27 17:04:25 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, t_size len)
{
	char	*ptr;
	t_size	i;
	t_size	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (len + start > ft_strlen(s))
		ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			ptr[j] = s[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
