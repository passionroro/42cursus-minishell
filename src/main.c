/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/05/16 10:42:07 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	command_access(t_minishell *sh, t_node *com, int ret)
{
	int	i;

	i = -1;
	if (com->args[0][0] != '/')
	{
		com->args[0] = add_backslash(com->args[0]);
		if (!com->args[0])
			return (ERR_MALLOC);
		while (sh->path[++i] && ret == -1)
		{
			com->path = ft_strjoin(sh->path[i], com->args[0]);
			if (!com->path)
				return (ERR_MALLOC);
			ret = access(com->path, F_OK);
			if (ret == -1)
				free(com->path);
		}
	}
	else
	{
		com->path = ft_strdup(com->args[0]);
		ret = access(com->path, F_OK);
	}
	return (ret);
}

int	command_exec(t_node *com, t_minishell *sh)
{
	if (ft_malloc_array(&sh->path, ':', sh->envp[12] + 5))
		return (ERR_MALLOC);
	if (ft_malloc_array(&com->args, ' ', com->content))
		return (ERR_MALLOC);
	if (command_access(sh, com, -1) == -1)
	{
		printf("zsh: command not found: %s\n", com->args[0] + 1);
		ft_free_array(com->args);
		return (-1);
	}
	return (execve(com->path, &com->args[0], sh->envp));
}

void	redirect(t_minishell *sh, t_node *com, int last)
{
	int	fd[2];

	pipe(fd);
	com->id = fork();
	if(com->id != 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		if (!last)
			dup2(fd[1], 1);
		close(fd[1]);
		command_exec(com, sh);
	}
}

int	is_real_command(t_minishell *sh)
{
	t_node	*com;
	t_node	*head;
	int		saved_fd;

	saved_fd = dup(0);
	com = list_init(sh);
	head = com;
	while (com)
	{
		if (com->next == NULL)
			redirect(sh, com, 1);
		else
			redirect(sh, com, 0);
		com = com->next;
	}
	while (head)
	{
		waitpid(head->id, NULL, 0);
		head = head->next;
	}
	dup2(saved_fd, 0);
	close(saved_fd);
	return (0);
}

//check for $ sign and the following word
//deal with quotes: single quotes prints the word itself (so 'PATH' prints < PATH >), double quotes make evrything inside them one string (so ECHO "bla bla" prints < bla bla >).
//fix the signals

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;

	(void)argv;
	(void)argc;
	sh.envp = envp;

	while (1)
	{
		sh.input = readline("[prompt]$ ");
		if (input_isnt_empty(sh.input))
		{
			add_history(sh.input);
			ret_val = is_real_command(&sh);
		}
		free(sh.input);
	}
	return (0);
}
