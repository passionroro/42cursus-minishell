/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:30:33 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/12 16:16:05 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_home(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "HOME=", 5))
            return (env[i] + 5);
	ft_putstr_fd("bash: cd: HOME not set\n", 1);
	return (NULL);
}

int	old_pwd(char **env, t_node *com)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			chdir(env[i] + 7);
			replace_pwd(com, env[i] + 7);
			ft_putstr_fd(env[i] + 7, 1);
			ft_putchar_fd('\n', 1);
            return (1);
		}
	}
	ft_putstr_fd("bash: cd: OLDPWD not set\n", 1);
	return (1);
}

int	run_cd(t_node *com)
{
	if (com->args[1] == NULL)
	{
		replace_pwd(com, get_home(com->sh->envp));
		return (chdir(get_home(com->sh->envp)));
	}
	if (com->args[1][0] == '-')
		return (old_pwd(com->sh->envp, com));
	chdir(com->args[1]);
	replace_pwd(com, getcwd(NULL, 0));
	return (1);
}
