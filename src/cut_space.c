/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:20:42 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 18:17:57 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cut_no_space(t_node *com, int *l, int *i)
{
	char	*new;
	char	*temp;
	int		c;

	new = (char *)malloc(sizeof(char) * (*i + 1));
	c = -1;
	while (++c < *i)
		new[c] = com->args[*l][c];
	new[c] = '\0';
	temp = com->args[*l];
	com->args[*l] = new;
	free(temp);
}

void	cut_space_after(t_node *com, int *l, int *i)
{
	int	p;

	cut_no_space(com, l, i);
	free(com->args[*l + 1]);
	p = 0;
	while (com->args[*l + ++p + 1])
		com->args[*l + p] = com->args[*l + p + 1];
	free(com->args[*l + p]);
	com->args[*l + p] = NULL;
}

void	cut_space_around(t_node *com, int *l, int *i)
{
	int	p;
	(void)i;
	free(com->args[*l]);
	free(com->args[*l + 1]);
	p = 0;
	while (com->args[*l + ++p + 1])
		com->args[*l + p - 1] = com->args[*l + p + 1];
	free(com->args[*l + --p]);
	com->args[*l + p] = NULL;
	free(com->args[*l + ++p]);
	com->args[*l + p] = NULL;
}

void	cut_space_before(t_node *com, int *l, int *i)
{
	int	p;

	(void)i;
	free(com->args[*l]);
	p = 0;
	while (com->args[*l + ++p])
		com->args[*l + p - 1] = com->args[*l + p];
	free(com->args[*l + --p]);
	com->args[*l + p] = NULL;
}

void	clean_command(t_node *com, int *l, int *i)
{
	if (com->args[*l][*i - 1] != '\0')
	{
		if (com->args[*l][*i + 1] != '\0')
			cut_no_space(com, l, i);
		else
			cut_space_after(com, l, i);
	}
	else
	{
		if (com->args[*l][*i + 1] == '\0')
			cut_space_around(com, l, i);
		else
			cut_space_before(com, l, i);
	}
}