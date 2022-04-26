/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:46:02 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/25 15:58:49 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*malloc_len(char *s, int len)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * (len + 1));
	new[len] = '\0';
	while (--len >= 0)
		new[len] = s[len];
	//maybe free s here
	return (new);
}

int	new_node(t_node *com, char *str, int len, int ret)
{
	t_node	*new;

	if (str[ret] == '\0')
		len++;
	//printf("str recieved in function: %s\n", str);
	new = (t_node *)malloc(sizeof(t_node));
	new->content = malloc_len(str, len);
	new->next = NULL;
	while (com->next != NULL)
		com = com->next;
	com->next = new;
	return (ret);
}

