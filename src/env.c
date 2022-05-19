/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:37:28 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 18:39:57 by rohoarau         ###   ########.fr       */
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

int	run_env(t_node *com, int out)
{
	int	i;

	i = -1;
	while (com->sh->envp[++i])
	{
		ft_putstr_fd(com->sh->envp[i], out);
		ft_putchar_fd('\n', out);
	}
	g_ret = 0;
	return (1);
}
