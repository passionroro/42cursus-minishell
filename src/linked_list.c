/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:03:43 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/26 17:09:49 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	one_line_less(t_clean_space *cs, char **str)
{
	cs->temp = ft_strdup(str[cs->i]);
	free(str[cs->i]);
}

char	**ft_clean_space(char **str)
{
	t_clean_space	cs;

	cs.i = -1;
	while (str[++cs.i])
	{
		cs.b = 0;
		while (str[cs.i][cs.b] == ' ')
			cs.b++;
		cs.e = 0;
		while (str[cs.i][cs.e])
			cs.e++;
		while (str[cs.i][--cs.e] == ' ')
			;
		one_line_less(&cs, str);
		str[cs.i] = (char *)malloc(sizeof(char) * (cs.e - cs.b) + 2);
		cs.l = -1;
		while (cs.b <= cs.e)
		{
			str[cs.i][++cs.l] = cs.temp[cs.b];
			cs.b++;
		}
		str[cs.i][++cs.l] = '\0';
		free(cs.temp);
	}
	return (str);
}

void	ft_free_list(t_node *com)
{
	t_node	*tmp;

	while (com)
	{
		tmp = com;
		free(com->content);
		com = com->next;
		free(tmp);
	}
}

void	new_node(t_node *com, char *str)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->content = ft_strdup(str);
	new->next = NULL;
	while (com->next != NULL)
		com = com->next;
	new->last = com;
	com->next = new;
	com->path = NULL;
	com->args = NULL;
}

t_node	*list_init(t_minishell *sh)
{
	t_node	*com;
	char	**commands;
	int		i;

	commands = ft_split_for_quotes(sh->input, '|');
	i = -1;
	while (commands[++i])
		commands[i] = ft_strtrim(commands[i], " ");
	com = (t_node *)malloc(sizeof(t_node));
	com->content = ft_strdup(commands[0]);
	com->next = NULL;
	com->last = NULL;
	com->path = NULL;
	com->args = NULL;
	i = 0;
	while (commands[++i])
		if (commands[i][0] != '\0')
			new_node(com, commands[i]);
	ft_free_array(commands);
	return (com);
}
