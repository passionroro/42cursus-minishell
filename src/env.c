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

char	*env_replace(t_node *com, int pos)
{
	char	*tmp;

	tmp = ft_strdup(com->args[1]);
	free(com->sh->envp[pos]);
	return (tmp);
}

char	**env_create(t_node *com, int size)
{
	int		i;
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (com->sh->envp[++i])
	{
		tmp[i] = ft_strdup(com->sh->envp[i]);
		free(com->sh->envp[i]);
	}
	free(com->sh->envp);
	tmp[i] = ft_strdup(com->args[1]);
	tmp[i + 1] = 0;
	return (tmp);
}

int	run_env(t_node *com)
{
	int	i;

	i = -1;
	while (com->sh->envp[++i])
		printf("%s\n", com->sh->envp[i]);
	g_ret = 0;
	return (1);
}
