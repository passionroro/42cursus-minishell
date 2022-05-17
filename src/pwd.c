/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:20:42 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/12 16:24:07 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_pwd_pos(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PWD=", 4))
			return (i);
	return (-1);
}

void	replace_pwd(t_node *com, char *dir)
{
	int		pos;

	pos = get_pwd_pos(com->sh->envp);
	free(com->sh->envp[pos]);
	com->sh->envp[pos] = ft_strjoin(ft_strdup("PWD="), dir);
	free(dir);
}

int	run_pwd(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			ft_putstr_fd(env[i] + 4, 1);
			ft_putchar_fd('\n', 1);
            return (1);
		}
	}
	return (-1);
}
