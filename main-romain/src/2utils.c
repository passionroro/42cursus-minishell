/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:46:02 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/27 17:10:11 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

char	*malloc_len(char *s, int len)
{
	int		end;
	int		start;
	char	*new;

	start = 0;
	end = len;
	while (is_white_space(s[start]) == 1 || s[start] == '|')
	{
		start++;
		len--;
	}
	while (is_white_space(s[end - 1]) || s[end - 1] == '|')
	{
		end--;
		len--;
	}
	new = ft_substr(s, start, len);
	if (!new)
		return (NULL);
	return (new);
}

int	new_node(t_node *com, char *str, int start, int end)
{
	t_node	*new;

	if (str[end - 1] == '\0')
		end++;
	new = (t_node *)malloc(sizeof(t_node));
	new->content = malloc_len(str, end - start);
	new->next = NULL;
	while (com->next != NULL)
		com = com->next;
	new->last = com;
	com->next = new;
	return (end);
}
