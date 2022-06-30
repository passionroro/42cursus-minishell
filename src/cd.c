/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:47:35 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/30 16:41:19 by rohoarau         ###   ########.fr       */
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
	return (NULL);
}

int	old_pwd(char **env, t_node *com, t_minishell *sh)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			if (chdir(env[i] + 7) == -1)
				return (printf("minishell: cd: %s: No such file or directory\n"\
							, env[i] + 7));
			tmp = getcwd(NULL, 0);
			replace_pwd(com, env[i] + 7, 0);
			printf("%s\n", env[i] + 7);
			free(sh->envp[i]);
			sh->envp[i] = ft_strjoin(ft_strdup("OLDPWD="), tmp);
			free(tmp);
			return (1);
		}
	}
	return (write_error("minishell: cd: OLDPWD not set\n", NULL, NULL, 1));
}

int	run_cd(t_node *com, t_minishell *sh)
{
	if (com->args[1] == NULL || !ft_strncmp(com->args[1], "~\0", 2))
	{
		if (get_home(sh->envp) == NULL)
			return (write_error("minishell: cd: HOME not set\n", NULL, NULL, 0));
		replace_old_pwd(com);
		replace_pwd(com, get_home(sh->envp), 0);
		return (chdir(get_home(sh->envp)));
	}
	if (!ft_strncmp(com->args[1], "-\0", 2))
		return (old_pwd(sh->envp, com, sh));
	if (chdir(com->args[1]) == -1)
	{
		write_error("minishell: cd: ", NULL, com->args[1], 0);
		return (write_error(": No such file or directory\n", NULL, NULL, 0));
	}
	replace_old_pwd(com);
	replace_pwd(com, getcwd(NULL, 0), 1);
	g_ret = 0;
	return (1);
}
