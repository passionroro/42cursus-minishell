/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:48:05 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/28 13:53:42 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, t_size num)
{
	t_size	i;
	char	*ptr;

	ptr = (char *)str;
	i = 0;
	while (i < num)
	{
		ptr[i] = c;
		i++;
	}
	return (str);
}
