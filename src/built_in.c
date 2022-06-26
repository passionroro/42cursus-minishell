/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:46:20 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/26 16:58:06 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_built_in(char **env, char *str)
{
	if (!ft_strncmp(str, "env\0", 4) && get_path(env) == NULL)
	{
		g_ret = 127;
		return (0);
	}
	if (!ft_strncmp(str, "export\0", 7)
		|| !ft_strncmp(str, "unset\0", 6)
		|| !ft_strncmp(str, "env\0", 4)
		|| !ft_strncmp(str, "exit\0", 5)
		|| !ft_strncmp(str, "cd\0", 3)
		|| !ft_strncmp(str, "echo\0", 5)
		|| !ft_strncmp(str, "pwd\0", 4))
		return (1);
	return (0);
}

int	built_in_check(t_node *com)
{
	if (!ft_strncmp(com->args[0], "export\0", 7))
		run_export(com);
	if (!ft_strncmp(com->args[0], "unset\0", 6))
		run_unset(com);
	if (!ft_strncmp(com->args[0], "env\0", 4))
		run_env(com);
	if (!ft_strncmp(com->args[0], "exit\0", 5))
		run_exit(com);
	if (!ft_strncmp(com->args[0], "cd\0", 3))
		run_cd(com);
	if (!ft_strncmp(com->args[0], "echo\0", 5))
		run_echo(com);
	if (!ft_strncmp(com->args[0], "pwd\0", 4))
		run_pwd(com->sh->envp);
	return (0);
}
