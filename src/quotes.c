/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:54:16 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/16 16:54:18 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_is_closed(t_minishell *sh)
{
	int		i;
	char	c;

	i = -1;
	sh->even = true;
	while (sh->input[++i])
	{
		if (sh->input[i] == 34 || sh->input[i] == 39)
		{
			c = sh->input[i];
			sh->even = !sh->even;
			while (sh->input[++i] && sh->input[i] != c)
				;
			if (sh->input[i] == c)
				sh->even = !sh->even;
		}
	}
	if (!sh->even)
		write_error("Error : open quotes\n", NULL, NULL, -1);
	return (sh->even);
}
