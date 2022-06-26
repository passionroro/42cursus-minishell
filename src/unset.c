/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:11:28 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 19:11:32 by henkaoua         ###   ########.fr       */
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

int	check_non_valid_identifier(t_node *com)
{
	int	j;
	int	i;

	j = 0;
	while (com->args[++j])
	{
		i = -1;
		while (com->args[j][++i])
		{
			if (!ft_isalpha(com->args[j][i]))
			{
				write_error("minishell: unset: `", NULL, com->args[j], 0);
				write_error("': not a valid identifier\n", NULL, NULL, 0);
				return (0);
			}
		}
	}
	return (1);
}

int	run_unset(t_node *c)
{
	int	i;
	int	len;

	if (c->args[1] == NULL)
		return (-1);
	if (!check_non_valid_identifier(c))
		return (-1);
	i = -1;
	while (c->sh->envp[++i])
	{
		len = 0;
		while (c->sh->envp[i][len] != '=')
			len++;
		if (!ft_strncmp(c->sh->envp[i], c->args[1], ft_strlen(c->args[1]))
			&& !ft_strncmp(c->sh->envp[i], c->args[1], len))
		{
			c->sh->envp = env_remove(c->sh->envp, i);
			break ;
		}
	}
	g_ret = 0;
	return (1);
}
