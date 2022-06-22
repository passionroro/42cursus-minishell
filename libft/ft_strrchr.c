/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:24:13 by henkaoua          #+#    #+#             */
/*   Updated: 2021/10/22 12:53:58 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	c = (unsigned char) c;
	str = (char *)s;
	while (*str != '\0')
		str++;
	if (c == '\0')
		return (str);
	while (str != (s - 1))
	{
		if (c == *str)
			return (str);
		str--;
	}
	return (0);
}
