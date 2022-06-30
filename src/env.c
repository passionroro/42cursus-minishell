/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:56:40 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 18:56:44 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_replace(t_node *com, int pos, t_minishell *sh)
{
	char	*tmp;

	tmp = ft_strdup(com->args[1]);
	free(sh->envp[pos]);
	return (tmp);
}

char	**env_create(t_node *com, int size, t_minishell *sh)
{
	int		i;
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (sh->envp[++i])
	{
		tmp[i] = ft_strdup(sh->envp[i]);
		free(sh->envp[i]);
	}
	free(sh->envp);
	tmp[i] = ft_strdup(com->args[1]);
	tmp[i + 1] = 0;
	return (tmp);
}

int	run_env(t_minishell *sh)
{
	int	i;

	i = -1;
	while (sh->envp[++i])
		printf("%s\n", sh->envp[i]);
	g_ret = 0;
	return (1);
}
