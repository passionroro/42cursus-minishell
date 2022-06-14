/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:36:40 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 19:36:45 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_check(t_node *com);

int	redirect_input(t_node *com, int i)
{
	int		fd;
	char	*file;

	while (ft_is_space(com->content[++i]) && com->content[i] != '\0')
		;
	file = write_file_name(com->content + i);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write_error("bash: ", file, ": No such file or directory\n",
				-1));
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

	while (ft_is_space(com->content[++i]) && com->content[i] != '\0')
		;
	file = write_file_name(com->content + i);
	if (file == NULL)
		return (write_error("bash: syntax error near unexpected \
		token `newline'\n", NULL, NULL, -1));
	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		return (write_error("Error : can't open file < ",
				file, " >\n", -1));
	dup2(fd, 1);
	close(fd);
	remove_file(com, '>');
	free(file);
	return (0);
}

int	redirect_heredoc(t_node *com, int i)
{
	char	*input;
	char	*container;
	char	*delimiter;

	i += 1;
	while (ft_is_space(com->content[++i]) && com->content[i] != '\0')
		;
	delimiter = write_file_name(com->content + i);
	if (delimiter == NULL)
		return (write_error("bash: syntax error near unexpected \
		token `newline'\n", NULL, NULL, -1));
	container = ft_strdup("");
	while (1)
	{
		input = readline("> ");
		if (input_isnt_empty(input, NULL))
			if (!ft_strcmp(input, delimiter))
				break ;
		container = ft_strjoin(container, input);
		container = ft_strjoin(container, "\n\0");
		free(input);
	}
	free(input);
	free(delimiter);
	remove_file(com, '<');
	redirect_check(com);
	printf("%s", container);
	free(container);
	return (-2);
}

int	redirect_append(t_node *com, int i)
{
	char	*file;
	int		fd;

	i += 1;
	while (ft_is_space(com->content[++i]) && com->content[i] != '\0')
		;
	file = write_file_name(com->content + i);
	if (file == NULL)
		return (write_error("bash: syntax error near unexpected \
		token `newline'\n", NULL, NULL, -1));
	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (write_error("Error : can't open file < ", file, " >\n", -1));
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
