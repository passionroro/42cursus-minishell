/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:40:14 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/18 20:56:17 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define READ 0
#define WRITE 1

int	is_built_in(char *str)
{
	if (!ft_strncmp(str, "export\0", 7)
		|| !ft_strncmp(str, "unset\0", 6)
		|| !ft_strncmp(str, "env\0", 4)
		|| !ft_strncmp(str, "exit\0", 5)
		|| !ft_strncmp(str, "cd\0", 3)
		|| !ft_strncmp(str, "echo\0", 5)
		|| !ft_strncmp(str, "pwd\0", 4))
		return (1);
	return (0);
}

void	built_in_redirect(t_node *com)
{
	int	fd[2];

	pipe(fd);
	if (com->last == NULL)
	{
		if (com->next == NULL)
			return ;
		else
		{
			close(fd[READ]);
			dup2(fd[WRITE], WRITE);
			close(fd[WRITE]);
		}
	}
	else if (com->next != NULL && com->last != NULL)
	{
		close(fd[WRITE]);
		dup2(fd[READ], READ);
		close(fd[READ]);
		dup2(fd[WRITE], WRITE);
		close(fd[WRITE]);
	}
	else if (com->next == NULL)
	{
		close(fd[WRITE]);
		close(fd[READ]);
	}
}

void	built_in_check(t_node *com)
{
	built_in_redirect(com);
	if (!ft_strncmp(com->args[0], "export\0", 7))
		ret_val =run_export(com);
	if (!ft_strncmp(com->args[0], "unset\0", 6))
		ret_val = run_unset(com);
	if (!ft_strncmp(com->args[0], "env\0", 4))
        ret_val = run_env(com);
	if (!ft_strncmp(com->args[0], "exit\0", 5))
		;
	//idk what to do with exit
	if (!ft_strncmp(com->args[0], "cd\0", 3))
		ret_val = run_cd(com);
	if (!ft_strncmp(com->args[0], "echo\0", 5))
		ret_val = run_echo(com);
	if (!ft_strncmp(com->args[0], "pwd\0", 4))
		ret_val = run_pwd(com->sh->envp);
//	free_var_init(com);
}
