/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:47:35 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 18:48:10 by henkaoua         ###   ########.fr       */
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
	printf("bash: cd: HOME not set\n");
	return (NULL);
}

int	old_pwd(char **env, t_node *com)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			tmp = getcwd(NULL, 0);
			chdir(env[i] + 7);
			replace_pwd(com, env[i] + 7, 0);
			printf("%s\n", env[i] + 7);
			free(com->sh->envp[i]);
			com->sh->envp[i] = ft_strjoin(ft_strdup("OLDPWD="), tmp);
			free(tmp);
			return (1);
		}
	}
	printf("bash: cd: OLDPWD not set\n");
	return (1);
}

int	run_cd(t_node *com)
{
	if (com->args[1] == NULL || !ft_strncmp(com->args[1], "~\0", 2))
	{
		replace_old_pwd(com);
		replace_pwd(com, get_home(com->sh->envp), 0);
		return (chdir(get_home(com->sh->envp)));
	}
	if (!ft_strncmp(com->args[1], "-\0", 2))
		return (old_pwd(com->sh->envp, com));
	chdir(com->args[1]);
	replace_old_pwd(com);
	replace_pwd(com, getcwd(NULL, 0), 1);
	g_ret = 0;
	return (1);
}
