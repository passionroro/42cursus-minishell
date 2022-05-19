/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:47:47 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 18:47:50 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_init(t_node *com)
{
	while (com->next)
	{
		if (pipe(com->fd) == -1)
			return ;
		com = com->next;
	}
}

void	first_redirection(t_node *com)
{
	close(com->next->fd[1]);
	dup2(1, com->next->fd[0]);
	close(com->next->fd[0]);
	com->fd[1] = com->next->fd[0];
}

void	middle_redirection(t_node *com)
{
	close(com->fd[1]);
	close(com->last->fd[0]);
	dup2(com->fd[0], com->last->fd[1]);
	close(com->fd[0]);
	close(com->last->fd[1]);
	com->fd[0] = com->last->fd[1];
	close(com->next->fd[1]);
	dup2(com->fd[1], com->next->fd[0]);
	close(com->fd[1]);
	close(com->next->fd[0]);
	com->fd[1] = com->next->fd[0];
}

void	last_redirection(t_node *com)
{
	close(com->fd[1]);
	close(com->last->fd[0]);
	dup2(com->fd[0], com->last->fd[1]);
	close(com->fd[0]);
	close(com->last->fd[1]);
	com->fd[0] = com->last->fd[1];
	com->fd[1] = 1;
}

void	built_in_redirect(t_node *com)
{
	if (com->last == NULL)
	{
		pipe_init(com);
		if (com->next == NULL)
			return ;
		else
			first_redirection(com);
	}
	else if (com->next != NULL && com->last != NULL)
		middle_redirection(com);
	else if (com->next == NULL)
		last_redirection(com);
}
