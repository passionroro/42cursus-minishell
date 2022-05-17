/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/05/17 14:58:10 by rohoarau         ###   ########.fr       */
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
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": No such file or directory", 1);
	ft_putchar_fd('\n', 1);
	return (NULL);
}

int	dollar_sign_access(char *str, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(str, env[i], ft_strlen(str)))
			return (i);
	return (0);
}

void	dollar_sign_check(t_node *com)
{
	int	pos;
	int	i;
	int	j;

	i = -1;
	while (com->args[++i])
	{
		if (com->args[i][0] == '$')
		{
			pos = dollar_sign_access(com->args[i] + 1, com->sh->envp);
			if (pos != 0)
			{
				j = -1;
				while (com->sh->envp[pos][++j] != '=')
					;
				free(com->args[i]);
				com->args[i] = ft_strdup(com->sh->envp[pos] + j + 1);
			}
		}
	}
}

int	command_exec(t_node *com, t_minishell *sh)
{
	if (ft_malloc_array(&com->args, ' ', com->content))
		return (ERR_MALLOC);
	dollar_sign_check(com);
	if (ft_malloc_array(&sh->path, ':', get_path(sh->envp, com->args[0])))
		return (ERR_MALLOC);
	if (command_access(sh, com, -1) == -1)
		return (-1);
	return (execve(com->path, &com->args[0], sh->envp));
}

int	is_real_command(t_node *com)
{
	while (com)
	{
		if (built_in_check(com) == -1)
		{
			com->id = fork();
			if (com->id == 0)
				return (command_exec(com, com->sh));
			else
				waitpid(com->id, NULL, 0);
		}
		com = com->next;
	}
	return (-1);
}

//check for $ sign and the following word
//deal with quotes: single quotes prints the word itself (so 'PATH' prints < PATH >), double quotes make evrything inside them one string (so ECHO "bla bla" prints < bla bla >).
//fix the signals

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	ft_signals(struct termios *save)
{
	struct termios	new;

	tcgetattr(STDIN_FILENO, save);
	new = *save;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sh;
	struct termios	save;

	(void)argv;
	(void)argc;
	sh.envp = env_init(envp);
	sh.exit = 0;
	ft_signals(&save);
	while (!sh.exit)
	{
		sh.input = readline("[prompt]$ ");
		if (input_isnt_empty(sh.input))
		{
			add_history(sh.input);
			sh.com = list_init(&sh);
			if (built_in_check(sh.com) == -1)
			{
				if (fork() == 0)
					sh.exit = is_real_command(sh.com);
				else
					wait(NULL);
			}
			ft_free_list(sh.com);
		}
		free(sh.input);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &save);
	return (0);
}
