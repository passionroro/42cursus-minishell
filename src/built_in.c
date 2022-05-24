/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:40:14 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 23:35:55 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_built_in2(char *str)
{
	if (!ft_strncmp(str, "export\0", 7)
		|| !ft_strncmp(str, "unset\0", 6)
		|| !ft_strncmp(str, "exit\0", 5)
		|| !ft_strncmp(str, "cd\0", 3)
		|| !ft_strncmp(str, "echo\0", 5)
		|| !ft_strncmp(str, "pwd\0", 4))
		return (1);
	return (0);
}

int	is_built_in(char **env, char *str)
{
	if (!ft_strncmp(str, "env\0", 4) && get_path(env, str) == NULL)
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

int	built_in_check(t_node *com, t_minishell *sh)
{
	int	out;
	
	built_in_redirect(com, sh);
	if  (com->next == NULL)
		out = sh->saved_fd[1];
	else
		out = com->next->fd[1];
	if (!ft_strncmp(com->args[0], "export\0", 7))
		run_export(com, com->fd[1]);
	if (!ft_strncmp(com->args[0], "unset\0", 6))
		run_unset(com);
	if (!ft_strncmp(com->args[0], "env\0", 4))
        run_env(com, com->fd[1]);
	if (!ft_strncmp(com->args[0], "exit\0", 5))
		run_exit(com, com->fd[1]);
	if (!ft_strncmp(com->args[0], "cd\0", 3))
		run_cd(com, com->fd[1]);
	if (!ft_strncmp(com->args[0], "echo\0", 5))
		run_echo(com, sh, out);
	if (!ft_strncmp(com->args[0], "pwd\0", 4))
		run_pwd(com->sh->envp, com->fd[1]);
	return (-2);
}
