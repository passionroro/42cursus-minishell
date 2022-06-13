/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:47:47 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 20:43:07 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	pipe_init(t_node *com)
{
	while (com->next)
	{
		if (com->builtin == true)
			if (pipe(com->fd) == -1)
				return ;
		com = com->next;
	}
}*/

void	first_redirection(t_node *com)
{
	dup2(com->next->fd[1], 1);
	close(com->next->fd[1]);
}

void	middle_redirection(t_node *com)
{
	if (com->last->last == NULL)
		dup2(com->fd[0], STDIN_FILENO);
	else
		dup2(com->fd[0], com->last->fd[0]);
	close(com->fd[0]);
	dup2(com->fd[1], com->last->fd[1]);
	close(com->fd[1]);
}

void	last_redirection(t_node *com)
{
	if (com->last->last == NULL)
		dup2(com->fd[0], STDIN_FILENO);
	else
		dup2(com->fd[0], com->last->fd[0]);
	close(com->fd[0]);
}

void	built_in_redirect(t_node *com, t_minishell *sh)
{
	if (com->next != NULL)
		pipe(com->next->fd);
	if (com->last == NULL)
	{
		if (com->next == NULL)
			return ;
		else
			first_redirection(com);
	}
	else if (com->next != NULL && com->last != NULL)
		middle_redirection(com);
	else if (com->next == NULL)
	{
		last_redirection(com);
		dup2(sh->saved_fd[1], 1);
	}
}
