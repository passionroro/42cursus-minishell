#include "../include/minishell.h"

char	*write_file_name(char *str)
{
	int		i;
	int		len;
	char	*new;

	if (!str)
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

/*
void	redirect_delimiter(t_node *com, int *l, int *i)
{
}*/

void	redirect_input(t_node *com, int *l, int *i)
{
	int		fd;
	char	*file;

	if (com->args[*l][*i + 1] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("\nbash: %s: No such file or directory\n", file);
		free(file);
		return ;
	}
	dup2(fd, 0);
	clean_command(com, l, i);
	close(fd);
	free(file);
}

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
	dup2(fd, STDOUT_FILENO);
	dup2(s_stdout, fd);
	close(s_stdout);
	free(file);
}

void	redirect_output(t_node *com, int *l, int *i)
{
	int		fd;
	char	*file;

	if (com->args[*l][*i + 1] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 1);
	if (file == NULL)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return ;
	}
	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
	{
		printf("Error : can't open file < %s >\n", file);
		return ;
	}
	dup2(fd, 1);
	clean_command(com, l, i);
	close(fd);
	free(file);
}

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
					;//redirect_delimiter(com, &l, &i);
				else
					redirect_input(com, &l, &i);
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
