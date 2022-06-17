/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:01:51 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/17 15:16:13 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
int	intlen(int nb)
{
	int	len;

	len = 0;
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

void	replace_dollar(t_node *com, int pos, int len)
{
	int		i;
	int		j;
	int		save;
	char	*tmp;

	save = pos;
	if (len == -1)
		while (com->content[pos++] != ' ' || com->content[pos] != '\0')
			len++;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - len));
	if (!tmp)
		return (NULL);
	i = -1;
	while (com->content[++i])
	{
		if (i < save || i > save)
			tmp[++j] = str[i];
	}
	tmp[++j] = 0;
	free(com->content);
	com->content = ft_strdup(tmp);
	ft_free_array(com->args);
	ft_malloc_array(com->args, ' ', tmp);
	free(tmp);
}

int	dollar_sign_access(t_node *com, char **env)
{
	int	i;
	int	j;
	int	len;

	j = -1;
	while (com->args[++j])
		if (!ft_strncmp(com->args[j], "$?\0", 3))
			return (-1);
	i = -1;
	while (env[++i])
	{
		while (env[i][++len] != '=')
			;
		j = -1;
		while (com->args[++j])
			if (!ft_strncmp(com->args[j], env[i], len))
				return (i);
	}
	return (-2);
}

void	dollar_sign_check(t_node *com)
{
	int	i;
	int	pos;

	i = -1;
	while (com->content[++i])
	{
		if (com->content[i] == '$')
		{
			if (dollar_single_quote(com->content, i) == 1)
				return ;
			pos = dollar_sign_access(com, com->sh->envp);
			if (pos == -2)
				return (replace_dollar(com, i, -1));
			if (pos == -1)
				return (replace_dollar(com, i, intlen(g_ret) + 1));
			if (pos > -1)
		}
	}

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
			pos = dollar_sign_access(com->args[i], com->sh->envp);
			if (pos > -1)
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
		if (com->content[i] == c && com->content[i - 1] != '\\')
			count++;
	if (count == 0)
		return (0);
	if (count % 2 != 0)
	{
		ft_putstr_fd("Please close the quotes.\n", 2);
		g_ret = 0;
		return (-1);
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
}*/

int	var_init(t_minishell *sh, t_node *com)
{
	if (ft_malloc_array(&com->args, ' ', com->content))
		return (-1);
	if (ft_malloc_array(&sh->path, ':', get_path(sh->envp)))
		if (is_built_in2(com->args[0]) != 1)
			return (-1);
	return (0);
}
