#include "../include/minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
            return (env[i] + 5);
	return (NULL);
}

void	set_fd(t_minishell *sh, t_node *com)
{
	sh->nodes = 0;
	while (com)
	{
		sh->nodes++;
		if (com->next != NULL)
			pipe(com->fd);
		com = com->next;
	}
}

int	is_real_command(t_minishell *sh)
{
	t_node	*com;
	t_node	*head;
	t_node	*tmp;

	sh->saved_fd[0] = dup(0);
	sh->saved_fd[1] = dup(1);
	com = list_init(sh);
	set_fd(sh, com);
	head = com;
	tmp = com;
	while (com)
	{
		pipe_it_up(sh, com);
		com = com->next;
	}
	while (head)
	{
		exit_code(head->id);
		head = head->next;
	}
	dup2(sh->saved_fd[0], 0);
	dup2(sh->saved_fd[1], 1);
	close(sh->saved_fd[0]);
	close(sh->saved_fd[1]);
	ft_free_list(tmp);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_minishell		sh;
	struct termios	save;

	(void)argv;
	(void)argc;
	sh.envp = env_init(envp);
	g_ret = 0;
	ft_signals(&save);
	while (1)
	{
		sh.input = readline("[prompt]$ ");
		if (input_isnt_empty(sh.input, sh.envp))
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
