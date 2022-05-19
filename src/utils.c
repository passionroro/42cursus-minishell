/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:03:14 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 20:50:08 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_malloc_array(char ***str, char sep, char *line)
{
	*str = ft_split(line, sep);
	if (!*str)
		return (ERR_MALLOC);
	return (0);
}

void	ft_free_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	free_var_init(t_minishell *sh, t_node *com)
{
	ft_free_array(com->args);
	ft_free_array(sh->path);
}

char	*add_backslash(char *str)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!ptr)
		return (NULL);
	ptr[0] = '/';
	i = -1;
	while (str[++i])
		ptr[i + 1] = str[i];
	ptr[i + 1] = '\0';
	free(str);
	return (ptr);
}

int	input_isnt_empty(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr_fd("exit", 1);
		exit(1);
	}
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i])
		return (1);
	else
		return (0);
}
