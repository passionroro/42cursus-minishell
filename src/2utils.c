/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:46:02 by henkaoua          #+#    #+#             */
/*   Updated: 2022/05/18 17:15:33 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	new_node(t_node *com, char *str, t_minishell *sh)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->content = str;
	new->next = NULL;
	while (com->next != NULL)
		com = com->next;
	new->last = com;
	com->next = new;
	com->sh = sh;
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
		cs.temp = str[cs.i];
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

t_node	*list_init(t_minishell *sh)
{
	t_node	*com;
	int		i;

	sh->commands = ft_split(sh->input, '|');
	sh->commands = ft_clean_space(sh->commands);
	com = (t_node *)malloc(sizeof(t_node));
	com->content = sh->commands[0];
	com->next = NULL;
	com->last = NULL;
	com->sh = sh;
	i = 0;
	while (sh->commands[++i])
		new_node(com, sh->commands[i], sh);
	return (com);
}

void ft_free_list(t_node *com)
{
	t_node	*tmp;

    ft_free_array(com->sh->commands);
	while (com)
	{
		tmp = com;
		com = com->next;
		free(tmp);
	}
}
