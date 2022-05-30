/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:43:27 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/26 12:54:34 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rec(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		ft_rec(n / 10, fd);
		c = '8';
		write (fd, &c, 1);
		return ;
	}
	if (n < 0)
	{
		c = '-';
		write (fd, &c, 1);
		ft_rec(n * -1, fd);
	}
	if (n > 0)
	{
		ft_rec(n / 10, fd);
		c = (n % 10) + 48;
		write (fd, &c, 1);
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = '0';
	if (n == 0)
		write (fd, &c, 1);
	else
		ft_rec(n, fd);
}
