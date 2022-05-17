/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:06:27 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/12 15:04:06 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*trim_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!tmp)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] != '"')
			tmp[++j] = str[i];
	tmp[j + 1] = '\0';
	return (tmp);
}

int	norminette_go_to_hell(t_node *com, int i)
{
	i = 0;
	if (!ft_strncmp(com->args[1], "-n\0", 3))
		i++;
	while (com->args[++i])
	{
		ft_putstr_fd(com->args[i], 1);
		if (com->args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (ft_strncmp(com->args[1], "-n\0", 3))
		ft_putchar_fd('\n', 1);
	return (1);
}

int	run_echo(t_node *com)
{
	int		len;
	int		i;

	if (com->args[2] == NULL && !ft_strncmp(com->args[1], "-n\0", 3))
		return (1);
	if (com->args[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	len = ft_strlen(com->content);
	i = -1;
	while (com->content[++i])
	{
		if (com->content[i] == '"' && com->content[len - 1] == '"')
		{
			com->content = trim_quotes(com->content);
			ft_putstr_fd(com->content + i, 1);
			if (ft_strncmp(com->args[1], "-n\0", 3))
				ft_putchar_fd('\n', 1);
			free(com->content);
			return (1);
		}
	}
	return (norminette_go_to_hell(com, i));
}
