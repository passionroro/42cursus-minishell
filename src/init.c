/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:13:39 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/18 15:55:39 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	dollar_sign_access(char *str, char **env)
{
	int	i;
	int	j;

	j = -1;
	while (str[++j] != '$')
		;
	i = -1;
	while (env[++i])
		if (!ft_strncmp(str + j + 1, env[i], ft_strlen(str + j + 1)))
			return (i);
	return (0);
}

void	dollar_sign_check(t_node *com)
{
	int	pos;
	int	i;
	int	j;

	i = -1;
	while (com->args[++i])
	{
		if (com->args[i][0] == '$')
		{
			if (com->args[i][1] == '?' && com->args[i][2] == '\0')
				return (question_mark(&com->args[i]));
			pos = dollar_sign_access(com->args[i], com->sh->envp);
			if (pos != 0)
			{
				j = -1;
				while (com->sh->envp[pos][++j] != '=')
					;
				free(com->args[i]);
				com->args[i] = ft_strdup(com->sh->envp[pos] + j + 1);
			}
		}
	}
}

char	*remove_quotes(char *str, int count, char c)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1 - count));
	if (!tmp)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] != c)
			tmp[++j] = str[i];
	tmp[++j] = 0;
	free(str);
	return (tmp);
}

int	quotes_check(t_node *com, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (com->content[++i])
		if (com->content[i] == c)
			count++;
	if (count == 0)
		return (0);
	if (count % 2 != 0)
	{
		ft_putstr_fd("Please close the quotes.\n", 2);
		return (69);
	}
	if (count % 2 == 0)
	{
		com->content = remove_quotes(com->content, count, c);
		ft_free_array(com->args);
		ft_malloc_array(&com->args, ' ', com->content);
	}
	if (c == '"')
		dollar_sign_check(com);
	return (0);
}

int	var_init(t_minishell *sh, t_node *com)
{
	if (ft_malloc_array(&com->args, ' ', com->content))
		return (ERR_MALLOC);
	if (ft_malloc_array(&sh->path, ':', get_path(sh->envp, com->args[0])))
		return (ERR_MALLOC);
	ret_val = quotes_check(com, '"');
	if (ret_val != 0)
		return (-1);
	ret_val = quotes_check(com, '\'');
	if (ret_val != 0)
		return (-1);
	return (0);
}
