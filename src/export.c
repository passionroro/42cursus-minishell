/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:36:16 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 18:20:39 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * export with no arguments prints the env sorted in alphabetic order with 
 * double quotes between the variable
 * export doesn't work if the command doesn't have '='
 * export will create a new env if it's a new command, and will replace the
 * correct line if the command already exists
*/

void	print_export(char **tab, int out)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		ft_putstr_fd("declare -x ", out);
		j = 0;
		while (tab[i][j] != '=')
			ft_putchar_fd(tab[i][j++], out);
		ft_putstr_fd("=\"", out);
		ft_putstr_fd(tab[i] + j + 1, out);
		ft_putstr_fd("\"\n", out);
	}
}

char	**export_init(char **tab, char **tmp)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (tab[++i])
		tmp[i] = ft_strdup(tab[i]);
	tmp[i] = 0;
	return (tmp);
}

int	export_no_args(char **tab, int out)
{
	int		i;
	int		j;
	char	**tmp;
	char	*swap;

	i = -1;
	tmp = export_init(tab, NULL);
	while (tmp[++i])
	{
		j = i - 1;
		while (j >= 0 && ft_strncmp(tmp[j], tmp[j + 1], 25) > 0)
		{
			swap = ft_strdup(tmp[j]);
			free(tmp[j]);
			tmp[j] = ft_strdup(tmp[j + 1]);
			free(tmp[j + 1]);
			tmp[j + 1] = ft_strdup(swap);
			free(swap);
			j--;
		}
	}
	print_export(tmp, out);
	ft_free_array(tmp);
	return (1);
}

int	run_export(t_node *com, int out)
{
	int		i;
	int		len;
	char	*cmd;

	if (com->args[1] == NULL)
		return(export_no_args(com->sh->envp, out));
	len = -1;
	while (com->args[1][++len] != '=')
		if (com->args[1][len] == '\0')
			return (-1);
	cmd = ft_substr(com->args[1], 0, len);
	i = -1;
	while (com->sh->envp[++i])
	{
		if (!ft_strncmp(com->sh->envp[i], cmd, len))
		{
			com->sh->envp[i] = env_replace(com, i);
			break ;
		}
	}
	if (com->sh->envp[i] == NULL)
		com->sh->envp = env_create(com, i);
	free(cmd);
	g_ret = 0;
	return (1);
}
