#include "../include/minishell.h"

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

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

char	*write_file_name(char *str)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '<' && !ft_is_space(str[i]))
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] && str[i] != '>' && str[i] != '<' && !ft_is_space(str[i]))
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

//we may wanna save the input of heredoc somewhere so
//	'cat <<END'
//	> sentence writen
//	> with heredoc
//	> END
//	becomes
int	redirect_heredoc(t_node *com, int i)
{
	int		fd;
	char	*input;
	char	*file;

	i += 1;
	while (ft_is_space(com->content[++i]))
		;
	file = write_file_name(com->content + i);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	dup2(fd, 0);
	close(fd);
	remove_file(com, '<');
	free(file);
	return (0);
}

int	redirect_append(t_node *com, int i)
{
	char	*file;
	int		fd;

	i += 1;
	while (ft_is_space(com->content[++i]))
		;
	file = write_file_name(com->content + i);
	if (file == NULL)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		printf("Error : can't open file < %s >\n", file);
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	remove_file(com, '>');
	free(file);
	return (0);
}

int	redirect_input(t_node *com, int i)
{
	int		fd;
	char	*file;

	while (ft_is_space(com->content[++i]))
		;
	file = write_file_name(com->content + i);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("bash: %s: No such file or directory\n", file);
		free(file);
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	remove_file(com, '<');
	free(file);
	return (0);
}

int	redirect_output(t_node *com, int i)
{
	char	*file;
	int		fd;

	while (ft_is_space(com->content[++i]))
		;
	file = write_file_name(com->content + i);
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
	close(fd);
	remove_file(com, '>');
	free(file);
	return (0);
}

int	redirect_check(t_node *com)
{
	int	i;
	int	exit;

	i = -1;
	exit = 0;
	while (com->content[++i] && !exit)
	{
		if (com->content[i] == '<')
		{
			if (com->content[i + 1] == '<')
				exit = redirect_heredoc(com, i);
			else
				exit = redirect_input(com, i);
			i -= 1;
		}
		else if (com->content[i] == '>')
		{
			if (com->content[i + 1] == '>')
				exit = redirect_append(com, i);
			else
				exit = redirect_output(com, i);
			i -= 1;
		}
	}
	return (exit);
}
