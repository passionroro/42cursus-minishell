/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:46:02 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/27 11:53:30 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*malloc_len(char *s, int len)
{
	char	*new;

	new = NULL;
	if (s[0] == ' ' && s[len - 1] != ' ')
		new = ft_substr(s, 1, len - 1);
	else if (s[0] != ' ' && s[len - 1] == ' ')
		new = ft_substr(s, 0, len - 1);
	else if (s[0] == ' ' && s[len - 1] == ' ')
		new = ft_substr(s, 1, len - 2);
	else if (s[0] != ' ' && s[len - 1] != ' ')
		new = ft_substr(s, 0, len);
	if (!new)
		return (NULL);
	return (new);
}

int	new_node(t_node *com, char *str, int len, int ret)
{
	t_node	*new;

	if (str[ret] == '\0')
		len++;
	new = (t_node *)malloc(sizeof(t_node));
	new->content = malloc_len(str, len);
	new->next = NULL;
	while (com->next != NULL)
		com = com->next;
	new->last = com;
	com->next = new;
	return (ret);
}
