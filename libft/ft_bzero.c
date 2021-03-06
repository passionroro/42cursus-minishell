/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:14:46 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/26 13:17:55 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_bzero(void *ptr, int num)
{
	char	*str;
	int		i;

	str = ptr;
	i = 0;
	while (i < num)
	{
		str[i] = '\0';
		i++;
	}
}
