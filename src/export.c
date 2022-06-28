/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:52 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 18:58:54 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		printf("declare -x ");
		j = 0;
		while (tab[i][j] != '=')
			printf("%c", tab[i][j++]);
		printf("=\"%s\"\n", tab[i] + j + 1);
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

int	export_no_args(char **tab)
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
	print_export(tmp);
	ft_free_array(tmp);
	return (1);
}

int	run_export(t_node *com, t_minishell *sh)
{
	int		i;
	int		len;
	char	*cmd;

	if (com->args[1] == NULL)
		return (export_no_args(sh->envp));
	len = -1;
	while (com->args[1][++len] != '=')
		if (com->args[1][len] == '\0')
			return (-1);
	cmd = ft_substr(com->args[1], 0, len);
	i = -1;
	while (sh->envp[++i])
	{
		if (!ft_strncmp(sh->envp[i], cmd, len))
		{
			sh->envp[i] = env_replace(com, i, sh);
			break ;
		}
	}
	if (sh->envp[i] == NULL)
		sh->envp = env_create(com, i, sh);
	free(cmd);
	g_ret = 0;
	return (1);
}
