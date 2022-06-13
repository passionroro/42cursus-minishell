#include "../include/minishell.h"


int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

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
	while (str[++i] && i <= len && !(str[i] == '>' || str[i] == '<'))
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

int	redirect_input(t_node *com, int *l, int *i)
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
		return (-1);
	}
	dup2(fd, 0);
	clean_command(com, l, i);
	close(fd);
	free(file);
	return (0);
}

int	redirect_heredoc(t_node *com, int *l, int *i)
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
	{
		free(file);
		return (-1);
	}
	while (1)
	{
		input = readline("> "); 
		if (input_isnt_empty(input, NULL))
			if (!ft_strncmp(input, file, ft_strlen(file)))
				break ;
		free(input);
	}
	free(input);
	dup2(s_stdin, 0);
	close(s_stdin);
	close(fd);
	free(file);
	return (0);
}

int	redirect_append(t_node *com, int *l, int *i)
{
	(void)com;
	(void)l;
	(void)i;
}

void	ft_cut_file(t_node *com, int start, int end, int len)
{
	char	*tmp;
	int		i;
	int		j;
	
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(com->content) - len + 1));
	if (!tmp)
		return ;
	i = -1;
	j = -1;
	while (com->content[++i])
		if (i < start || i > end)
			tmp[++j] = com->content[i];
	tmp[j + 1] = '\0';
	free(com->content);
	com->content = ft_strdup(tmp);
	ft_free_array(com->args);
	ft_malloc_array(&com->args, ' ', tmp);
	free(tmp);
}

void	remove_file(t_node *com, char c)
{
	int	i;
	int start;

	i = -1;
	start = 0;
	while (com->content[++i])
	{
		if (com->content[i] == c && start == 0)
		{
			start = i;
			if (com->content[i + 1] == c)
				i += 1;
			i++;
		}
		if (start != 0)
		{
			if (com->content[i + 1] == '\0')
				return (ft_cut_file(com, start, i, i + 1 - start));
			else if (com->content[i] == '>' || com->content[i] == '<')
				return (ft_cut_file(com, start, i - 1, i - start));
		}
	}
}

int	redirect_output(t_node *com, int *l, int *i)
{
	char	*file;
	int		fd;

	if (com->args[*l][*i + 1] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 1);
	if (file == NULL)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
	{
		printf("Error : can't open file < %s >\n", file);
		return (-1);
	}
	dup2(fd, 1);
	remove_file(com, '>');
	close(fd);
	free(file);
	return (0);
}
//may want to use com->content instead of com->args
void	redirect_check(t_node *com)
{
	int	i;
	int	l;
	int	exit;

	l = -1;
	while (com->args[++l] && !exit)
	{
		i = -1;
		while (com->args[l][++i] && !exit)
		{
			if (com->args[l][i] == '<')
			{
				if (com->args[l][i + 1] == '<')
					exit = redirect_heredoc(com, &l, &i);
				else
					exit = redirect_input(com, &l, &i);
			}
			else if (com->args[l][i] == '>')
			{
				if (com->args[l][i + 1] == '>')
					exit = redirect_append(com, &l, &i);
				else
					exit = redirect_output(com, &l, &i);
			}
		}
	}
}
