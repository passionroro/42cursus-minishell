/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:04:08 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/25 11:28:05 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *cpy)
{
	char	*pst;
	int		i;

	i = 0;
	while (cpy[i])
		i++;
	pst = (char *)malloc((i + 1) * sizeof(const char));
	if (pst == NULL)
		return (0);
	i = 0;
	while (cpy[i])
	{
		pst[i] = cpy[i];
		i++;
	}
	pst[i] = '\0';
	return ((char *)pst);
}
