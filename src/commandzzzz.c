
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

int	command_exec(t_node *com, t_minishell *sh)
{
	if (command_access(sh, com, -1) == -1)
	{
		printf("bash: %s: command not found\n", com->args[0] + 1);
		g_ret = 127;
		if (!com->path)
			free(com->path);
		exit(g_ret);
		return (-1);
	}
	return (execve(com->path, &com->args[0], sh->envp));
}

void	pipe_redirection(t_node *com, t_minishell *sh)
{
	if (com->last == NULL && com->next == NULL)
		return ;
	if (com->next != NULL)
	{
		close(com->fd[0]);
		dup2(com->fd[1], 1);
		close(com->fd[1]);
	}
	else
		dup2(sh->saved_fd[1], 1);
}

int	command_not_found(t_minishell *sh, t_node *com)
{
	printf("bash: %s: No such file or directory\n", com->args[0]);
	free_var_init(sh, com);
	g_ret = 127;
	return (g_ret);
}

int	pipe_it_up(t_minishell *sh, t_node *com)
{
	if (var_init(sh, com) != 0)
		return (command_not_found(sh, com));
	pipe_redirection(com, sh);
	if (redirect_check(com) != 0)
	{
		free_var_init(sh, com);
		return (-1);
	}
	com->id = fork();
	if (com->id == 0)
	{
		if (is_built_in(sh->envp, com->args[0]) != 1)
			return (command_exec(com, sh));
		exit (1);
	}
	if (is_built_in(sh->envp, com->args[0]) == 1)
		built_in_check(com);
	dup2(com->fd[0], 0);
	close(com->fd[0]);
	free_var_init(sh, com);
	return (0);
}
