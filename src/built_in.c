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

int	is_built_in(char **env, char **args)
{
	int		i;

	i = -1;
	while (args[++i])
	{
		if (!ft_strncmp(args[i], "env\0", 4) && get_path(env) == NULL)
		{
			g_ret = 127;
			return (0);
		}
		if (!ft_strncmp(args[i], "export\0", 7)
			|| !ft_strncmp(args[i], "unset\0", 6)
			|| !ft_strncmp(args[i], "env\0", 4)
			|| !ft_strncmp(args[i], "exit\0", 5)
			|| !ft_strncmp(args[i], "cd\0", 3)
			|| !ft_strncmp(args[i], "echo\0", 5)
			|| !ft_strncmp(args[i], "pwd\0", 4))
			return (1);
	}
	return (0);
}

int	built_in_check(t_node *com, t_minishell *sh)
{
	if (!ft_strncmp(com->args[0], "export\0", 7))
		run_export(com, sh);
	if (!ft_strncmp(com->args[0], "unset\0", 6))
		run_unset(com, sh);
	if (!ft_strncmp(com->args[0], "env\0", 4))
		run_env(sh);
	if (!ft_strncmp(com->args[0], "exit\0", 5))
		run_exit(com, sh);
	if (!ft_strncmp(com->args[0], "cd\0", 3))
		run_cd(com, sh);
	if (!ft_strncmp(com->args[0], "echo\0", 5))
		run_echo(com);
	if (!ft_strncmp(com->args[0], "pwd\0", 4))
		run_pwd(sh->envp);
	return (0);
}
