/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/28 15:13:25 by henkaoua         ###   ########.fr       */
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
		printf("zsh: command not found: %s\n", com->args[0]);
		ft_free_array(com->args);
		return (-1);
	}

	return (execve(com->path, &com->args[0], sh->envp));
}

int	is_real_command(t_minishell *sh)
{
	t_node	*com;

	com = list_init(sh);
	print_list(com);
	while (com)
	{
		com->id = fork();
		if (com->id == 0)
			return (command_exec(com, sh));
		else
			waitpid(com->id, NULL, 0);
		com = com->next;
	}
	return (-1);
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
	sh.exit = 0;
	while (!sh.exit)
	{
		sh.input = readline("[prompt]$ ");
		if (input_isnt_empty(sh.input))
		{
			add_history(sh.input);
			if (fork() == 0)
				sh.exit = is_real_command(&sh);
			else
				wait(NULL);
		}
		free(sh.input);
	}
	return (0);
}
