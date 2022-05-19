/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/05/19 15:43:41 by rohoarau         ###   ########.fr       */
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

char	*get_path(char **env, char *str)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
            return (env[i] + 5);
	if (is_built_in2(str) == 1)
		return (NULL);
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": No such file or directory", 1);
	ft_putchar_fd('\n', 1);
	return (NULL);
}

int	command_exec(t_node *com, t_minishell *sh)
{
	if (command_access(sh, com, -1) == -1)
	{
	/*	if (com->args[0][0] == '/')
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(com->args[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_ret = 128;
		}
		else
		{*/
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(com->args[0] + 1, 2);
			ft_putstr_fd(": command not found\n", 2);
			g_ret = 127;
		//}
		return (-1);
	}
	return (execve(com->path, &com->args[0], sh->envp));
}

int	redirect(t_minishell *sh, t_node *com, int last)
{
	int	fd[2];

	if (var_init(sh, com) != 0)
		return (g_ret);
	if (is_built_in(sh->envp, com->args[0]) == 1)
		return (built_in_check(com));
	pipe(fd);
	com->id = fork();
	if(com->id != 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		free_var_init(sh, com);
	}
	else
	{
		close(fd[0]);
		if (!last)
			dup2(fd[1], 1);
		close(fd[1]);
		return (command_exec(com, sh));
	}
	return (0);
}

void	exit_code(int id)
{
	int	wstatus;

	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_ret = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		g_ret = WTERMSIG(wstatus);
		if (g_ret != 131)
			g_ret += 128;
	}
}

int	is_real_command(t_minishell *sh)
{
	t_node	*com;
	t_node	*head;
	int		saved_fd;
	int		ret;

	saved_fd = dup(0);
	com = list_init(sh);
	head = com;
	while (com)
	{
		if (com->next == NULL)
			ret = redirect(sh, com, 1);
		else
			ret = redirect(sh, com, 0);
		com = com->next;
	}
	while (head)
	{
		if (ret > -1)
			exit_code(head->id);
		head = head->next;
	}
	dup2(saved_fd, 0);
	close(saved_fd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;
	struct termios	save;

	(void)argv;
	(void)argc;
	sh.envp = env_init(envp);
	g_ret = 0;
	ft_signals(&save);
	while (1)
	{
		sh.input = readline("[prompt]$ ");
		if (input_isnt_empty(sh.input))
		{
			add_history(sh.input);
			is_real_command(&sh);
		}
		free(sh.input);
	}
	ft_free_array(sh.envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &save);
	return (0);
}
