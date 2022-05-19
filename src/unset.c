/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:55:23 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 18:33:07 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**env_remove(char **str, int pos)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	while (str[++i])
		;
	tmp = (char **)malloc(sizeof(char *) * i);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (i == pos)
			free(str[i]);
		else
		{
			tmp[j] = ft_strdup(str[i]);
			free(str[i]);
			j++;
		}
	}
	free(str);
	tmp[j] = 0;
	return (tmp);
}

int	run_unset(t_node *com)
{
	int		i;

	if (com->args[1] == NULL)
		return (-1);
	i = -1;
	while (com->sh->envp[++i])
	{
		if (!ft_strncmp(com->sh->envp[i], com->args[1], ft_strlen(com->args[1])))
		{
			com->sh->envp = env_remove(com->sh->envp, i);
			break ;
		}
	}
	g_ret = 0;
	return (1);
}
