/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_fncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:41:01 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 19:41:02 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cut_file(t_node *com, int start, int end, int len)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(com->content) - len + 1));
	if (!tmp)
		return ;
	i = -1;
	j = -1;
	while (com->content[++i])
		if (i < start || i > end)
			tmp[++j] = com->content[i];
	tmp[j + 1] = '\0';
	free(com->content);
	com->content = ft_strdup(tmp);
	ft_free_array(com->args);
	ft_malloc_array(&com->args, ' ', tmp);
	free(tmp);
}

void	remove_file(t_node *com, char c)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	while (com->content[++i])
	{
		if (com->content[i] == c && start == 0)
		{
			start = i;
			if (com->content[i + 1] == c)
				i += 1;
			i++;
		}
		if (start != 0)
		{
			if (com->content[i + 1] == '\0')
				return (ft_cut_file(com, start, i, i + 1 - start));
			else if (com->content[i] == '>' || com->content[i] == '<')
				return (ft_cut_file(com, start, i - 1, i - start));
		}
	}
}

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

char	*write_file_name(char *str)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '<' && !ft_is_space(str[i]))
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] && str[i] != '>' && str[i] != '<' && !ft_is_space(str[i]))
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
