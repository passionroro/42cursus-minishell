/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:55:36 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 18:55:38 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//echo salut es amis 
int	run_echo(t_node *com)
{
	int	i;

	if (com->args[2] == NULL && !ft_strncmp(com->args[1], "-n\0", 3))
		return (1);
	if (com->args[1] == 0)
		return (printf("\n"));
	i = 0;
	if (!ft_strncmp(com->args[1], "-n\0", 3))
		i++;
	while (com->args[++i])
	{
		write (1, com->args[i], ft_strlen(com->args[i]));
		if (com->args[i + 1] != NULL)
			write (1, " ", 1);
	}
	if (ft_strncmp(com->args[1], "-n\0", 3)
		&& ft_strncmp(com->args[1], "\n\0", 2))
		printf("\n");
	g_ret = 0;
	return (1);
}
