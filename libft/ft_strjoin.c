/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:40:52 by rohoarau          #+#    #+#             */
/*   Updated: 2021/11/18 15:17:23 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	t_size	i;
	t_size	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (0);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		ptr[len] = s2[i];
		len++;
	}
	ptr[len] = '\0';
	return (ptr);
}
