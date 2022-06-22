/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:15:10 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/28 16:24:36 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(t_size count, t_size size)
{
	void	*vd;

	vd = (void *)malloc(count * size);
	if (!vd)
		return (0);
	ft_bzero(vd, count * size);
	return (vd);
}
