/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:36:53 by rohoarau          #+#    #+#             */
/*   Updated: 2021/10/22 14:27:30 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	str;

	if (n == 0)
		write (fd, "0", 1);
	if (n < 0)
	{
		write (fd, "-", 1);
		if (n == -2147483648)
			write (fd, "2147483648", 10);
		n *= -1;
	}
	if (n > 0)
	{
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		str = n % 10 + 48;
		write (fd, &str, sizeof(str));
	}
}
