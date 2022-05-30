#include "../include/minishell.h"

char	*get_path(char **env, char *str)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
            return (env[i] + 5);
	return (NULL);
}

int	is_real_command(t_minishell *sh)
{
	t_node	*com;
	t_node	*head;
	int		ret;

	sh->saved_fd[0] = dup(0);
	sh->saved_fd[1] = dup(1);
	com = list_init(sh);
	head = com;
	while (com)
	{
		if (com->next == NULL)
			ret = pipe_it_up(sh, com);
		else
			ret = pipe_it_up(sh, com);
		com = com->next;
	}
	while (head)
	{
		if (ret > -1)
			exit_code(head->id);
		head = head->next;
	}
	dup2(sh->saved_fd[0], 0);
	close(sh->saved_fd[0]);
	close(sh->saved_fd[1]);
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
		if (input_isnt_empty(&sh))
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