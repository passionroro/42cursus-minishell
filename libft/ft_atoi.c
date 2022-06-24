/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:49:34 by henkaoua          #+#    #+#             */
/*   Updated: 2022/02/09 12:47:21 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	num;
	int	i;
	int	g;

	num = 0;
	i = 0;
	g = 1;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == '-')
			g = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	num = num * g;
	return (num);
}
