#include "../include/minishell.h"

int	command_access(t_minishell *sh, t_node *com, int ret)
{
    int	i;

    i = -1;
    if (com->args[0][0] != '/')
    {
        com->args[0] = add_backslash(com->args[0]);
		if (!com->args[0])
			return (1);
		while (sh->path[++i] && ret == -1)
		{
			com->path = ft_strjoin(sh->path[i], com->args[0]);
			if (!com->path)
				return (1);
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

void	pipe_redirection(t_node *com)
{
    pipe(com->fd);
    com->id = fork();
	if(com->id != 0)
	{
		close(com->fd[1]);
		dup2(com->fd[0], STDIN_FILENO);
		close(com->fd[0]);
	}
	else
	{
		close(com->fd[0]);
		if (com->next != NULL)
			dup2(com->fd[1], 1);
		close(com->fd[1]);
	}
}

int	command_exec(t_node *com, t_minishell *sh)
{
	if (command_access(sh, com, -1) == -1)
	{
		if (com->args[0][0] == '/')
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(com->args[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_ret = 128;
		}
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(com->args[0] + 1, 2);
			ft_putstr_fd(": command not found\n", 2);
			g_ret = 127;
		}
		return (-1);
	}
	return (execve(com->path, &com->args[0], sh->envp));
}

int	pipe_it_up(t_minishell *sh, t_node *com)
{
	if (var_init(sh, com) != 0)
		return (g_ret);
	//redirect_check(com);
    pipe_redirection(com);
    if (com->id == 0)
    {
        if (is_built_in(sh->envp, com->args[0]) != 1)
            return (command_exec(com, sh));
        exit (1);
    }
    if (is_built_in(sh->envp, com->args[0]) == 1)
    {
        dup2(com->fd[1], 1);
        return (built_in_check(com));
    }
    free_var_init(sh, com);
	return (0);
}
