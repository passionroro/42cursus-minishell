/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:16:31 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 18:16:00 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_exit(t_node *com, int out)
{
	int	i;

	ft_putstr_fd("exit\n", out);
	if (com->args[1] == NULL)
		exit(0);
	if (com->args[1] != NULL && com->args[2] != NULL)
		ft_putstr_fd("bash: exit: too many arguments\n", out);
	i = -1;
	if (com->args[1] != NULL && com->args[2] == NULL)
	{
		while (ft_isdigit(com->args[1][++i]) == 1)
			;
		if (com->args[1][i] != '\0')
			ft_putstr_fd("bash: exit: numeric argument required\n", out);
	}
	free_var_init(com->sh, com);
	ft_free_list(com);
	exit(0);
	return (0);
}
