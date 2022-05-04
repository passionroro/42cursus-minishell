/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/05/03 16:33:32 by rohoarau         ###   ########.fr       */
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

void	redirect_output(t_node *com)
{
	if (com->next == NULL && com->last == NULL)		//only one element
		return ;

/*	else if (com->next != NULL && com->last == NULL)		//output of first becomes input of next	
	{
		printf("FIRST {%s}\n", com->content);
//		close(com->fd[1]);
		dup2(com->fd[0], STDOUT_FILENO);
//		close(com->fd[0]);
	}
	else if (com->next == NULL && com->last != NULL)	//output of last becomes STDIN
	{
		printf("LAST {%s}\n", com->content);
		dup2(com->last->fd[1], STDIN_FILENO);
		//close(com->fd[0]);
		//dup2(com->fd[1], STDIN_FILENO);
		//close(com->fd[1]);
	}*/
}
/*
void	ft_replace_env(t_node *com, char *ptr, int i)
{
	int		j;
	char	*str;

	com->sh->my_env[i] = 0;
	i = -1;
	j = -1;
	while (com->args[i][++j] != '=')
		;
	str = ft_substr(com->args[i], 0, j);
	while (com->sh->my_env[++i])
	{
		if (!ft_strncmp(com->sh->my_env[i], ptr, j))
		{
			free(com->sh->my_env[i]);
			com->sh->my_env[i] = ft_strdup(com->args[i]);
		}
	}
	free(str);
}

int	env_print(t_node *com)
{
	int	i;

	i = -1;
	while (com->sh->my_env[++i])
	{
		ft_putstr_fd(com->sh->my_env[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (1);
}

int	env_malloc(t_node *com, char *ptr, int size)
{;

	i = -1;
	while (com->sh->envp[++i])
		;
	com->sh->my_env = (char **)malloc(sizeof(char *) * (i + size));
	i = -1;
	while (com->sh->envp[++i])
		com->sh->my_env[i] = ft_strdup(com->sh->envp[i]);
	int	i
//	if (size == 1)
//		= 0
//		ft_replace_env(com, ptr, i);
	if (size == 2)
	{
		com->sh->my_env[i] = ft_strdup(com->args[1]);
		com->sh->my_env[i + 1] = 0;
	}
	ptr = NULL;
	env_print(com);
	//ft_free_array(com->sh->my_env);
	return (1);
}

int	run_env(t_node *com, char **env)
{
	int	i;

	i = -1;
	if (!env)
		while (com->sh->envp[++i])
			printf("%s\n", com->sh->envp[i]);
	else
		while (env[++i])
			printf("AHHHHHHH%s\n", env[i]);
	return (1);
}

int	run_export(t_node *com)
{
	int		i;
	char	*ptr;

	i = -1;
	if (com->args[1] == NULL)
		return (-1);
	while (com->args[1][++i] != '=')
		if (com->args[1][i] == '\0')
			return (-1);
	ptr = ft_substr(com->args[1], 0, i);
	if (!ptr)
		return (-1);
	if (getenv(ptr) == NULL)
		env_malloc(com, ptr, 2);
	else
		env_malloc(com, ptr, 1);
	free(ptr);
	return (1);
}*/

char	**env_init(t_node *com)
{
	int	i;

	i = -1;
	while (com->sh->envp[++i])
		;
	com->sh->my_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!com->sh->my_env)
		return (NULL);
	i = -1;
	while (com->sh->envp[++i])
	{
		com->sh->my_env[i] = ft_strdup(com->sh->envp[i]);
		if (!com->sh->my_env[i])
			return (NULL);
	}
	com->sh->my_env[i] = 0;
	return (com->sh->my_env);
}

int	run_env(t_node *com)
{
	int	i;

	if (!com->sh->my_env)
		com->sh->my_env = env_init(com);
	i = -1;
	while (com->sh->my_env[++i])
	{
		ft_putstr_fd(com->sh->my_env[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (1);
}

char	*env_replace(t_node *com, int pos)
{
	char	*tmp;

	tmp = ft_strdup(com->args[1]);
	free(com->sh->my_env[pos]);
	return (tmp);
}

char	**env_create(t_node *com, int size)
{
	int		i;
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (com->sh->my_env[++i])
	{
		tmp[i] = ft_strdup(com->sh->my_env[i]);
		free(com->sh->my_env[i]);
	}
	free(com->sh->my_env);
	tmp[i] = ft_strdup(com->args[1]);
	tmp[i + 1] = 0;
	i = -1;
	while (tmp[++i])
		printf("{%d}	%s\n", i, tmp[i]);
	return (tmp);
}

int	run_export(t_node *com)
{
	int		i;
	int		len;
	char	*cmd;

	if (com->args[1] == NULL)
		return (-1);
	if (!com->sh->my_env)
		com->sh->my_env = env_init(com);
	len = -1;
	while (com->args[1][++len] != '=')
		if (com->args[1][len] == '\0')
			return (-1);
	cmd = ft_substr(com->args[1], 0, len);
	i = -1;
	while (com->sh->my_env[++i])
	{
		if (!ft_strncmp(com->sh->my_env[i], cmd, len))
		{
			com->sh->my_env[i] = env_replace(com, i);
			break ;
		}
	}
	if (com->sh->my_env[i] == NULL)
		com->sh->my_env = env_create(com, i);
	free(cmd);
	return (1);
}

int	run_echo(t_node *com)
{
	int		i;
	int		last;
	char	*tmp;

	i = 0;
	while (com->args[++i])
	{
		last = ft_strlen(com->args[i]);
		if (com->args[i][0] == '"' && com->args[i][last - 1] == '"')
		{
			tmp = ft_strdup(com->args[i]);
			free(com->args[i]);
			com->args[i] = ft_strtrim(tmp, "\"");
			free(tmp);
		}
	}
	return (-1);
}
//AAAAA
int	built_in_check(t_node *com)
{
	if (!ft_strncmp(com->args[0], "/echo\0", 6))
		return (run_echo(com));
	if (!ft_strncmp(com->args[0], "/export\0", 8))
		return (run_export(com));
	if (!ft_strncmp(com->args[0], "/env\0", 5))
		return (run_env(com));
	if (!ft_strncmp(com->args[0], "/exit\0", 6))
		return (1);
	return (0);
}

int	command_exec(t_node *com, t_minishell *sh)
{
	if (ft_malloc_array(&sh->path, ':', sh->envp[12] + 5))
		return (ERR_MALLOC);
	if (ft_malloc_array(&com->args, ' ', com->content))
		return (ERR_MALLOC);
	command_access(sh, com, -1);
	built_in_check(com);
	if (!ft_strncmp(com->args[0], "/env", 4))
		return (1);
	if (!ft_strncmp(com->args[0], "/export", 7))
		return (1);
	return (execve(com->path, &com->args[0], sh->envp));
}

int	is_real_command(t_minishell *sh)
{
	t_node	*com;

	com = list_init(sh);
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
	int			id;

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
			id = fork();
			if (id == 0)
				sh.exit = is_real_command(&sh);
			else
				wait(NULL);
		}
		if (!ft_strncmp(sh.input, "exit", 4))
			if (id != 0)
				sh.exit = write(1, "exit\n", 5);
		free(sh.input);
	}
	return (0);
}
