#include "../include/minishell.h"

char	*write_file_name(char *str)
{
	int		i;
	int		len;
	char	*new;

	if (!str[0])
		return (NULL);
	len = 0;
	while (str[len] && !(str[len] == '>' || str[len] == '<'))
		len++;
	new = (char *)malloc(sizeof(char) * (len + 1));
	i = -1;
	while (str[++i] && i <= len)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

void	redirect_heredoc(t_node *com, int *l, int *i)
{
	int		s_stdin;
	int		fd;
	char	*input;
	char	*file;

	s_stdin = dup(STDIN_FILENO);
	if (com->args[*l][*i + 2] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 2);
	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (!fd)
		return ;
	while (1)
	{
		input = readline("> ");
		if (input_isnt_empty(input, NULL))
			if (!ft_strncmp(input, file, ft_strlen(file)))
				break ;
		free(input);
	}
	free(input);
	dup2(s_stdin, STDIN_FILENO);
	close(s_stdin);
	close(fd);
	free(file);
}
/*
void	redirect_input(t_node *com, int *l, int *i)
{
	int	s_stdin;
	int	fd;

	saved_stdin = dup(STDIN_FILENO);
	fd = open(com->args[*l - 1], );
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}
*/

void	redirect_append(t_node *com, int *l, int *i)
{
	int		s_stdout;
	int		fd;
	char	*file;

	s_stdout = dup(STDOUT_FILENO);
	if (com->args[*l][*i + 1] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 1);
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (!fd)
		return ;
	dup2(fd, STDOUT_FILENO);
	dup2(s_stdout, fd);
	close(s_stdout);
	close(fd);
	free(file);
}

void	redirect_output(t_node *com, int *l, int *i)
{
	int		s_stdout;
	char	*file;

	s_stdout = dup(STDOUT_FILENO);
	if (com->args[*l][*i + 1] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 1);
	com->fd[0] = open(file, O_WRONLY | O_CREAT, 0777);
	if (com->fd[0] == -1)
		;//no pipe : do something
	dup2(STDOUT_FILENO, com->fd[0]);
	clean_command(com, l, i);
	dup2(s_stdout, com->fd[0]);
	close(s_stdout);
	close(com->fd[0]);
	free(file);
}
//setting <i> and <l> after redicert functions!!
void	redirect_check(t_node *com)
{
	int	i;
	int	l;

	l = -1;
	while (com->args[++l])
	{
		i = -1;
		while (com->args[l][++i])
		{
			if (com->args[l][i] == '<')
			{
				if (com->args[l][i + 1] == '<')
					redirect_heredoc(com, &l, &i);
				else
					;//redirect_input(com, &l, &i);
			}
			else if (com->args[l][i] == '>')
			{
				if (com->args[l][i + 1] == '>')
					redirect_append(com, &l, &i);
				else
					redirect_output(com, &l, &i);
			}
		}
	}
}
