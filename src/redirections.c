/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:36:40 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/26 17:26:38 by rohoarau         ###   ########.fr       */
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
		return (write_error("minishell: ", file,
				": No such file or directory\n", -1));
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
		return (write_error("minishell: syntax error near unexpected \
token `newline'\n", NULL, NULL, -1));
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
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
	t_heredoc	her;

	i += 1;
	while (ft_is_space(com->content[++i]) && com->content[i] != '\0')
		;
	her.delimiter = write_file_name(com->content + i);
	if (her.delimiter == NULL)
		return (write_error("minishell: syntax error near unexpected \
token `newline'\n", NULL, NULL, -1));
	her.container = ft_strdup("");
	while (1)
	{
		her.input = readline("> ");
		if (input_isnt_empty(her.input, NULL))
			if (!ft_strcmp(her.input, her.delimiter))
				break ;
		her.container = ft_strjoin(her.container, her.input);
		her.container = ft_strjoin(her.container, "\n\0");
		free(her.input);
	}
	heredoc_part2(&her, com);
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
		return (write_error("minishell: syntax error near unexpected \
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

int	is_open_quotes(t_node *c, int len)
{
	int		i;
	bool	dq;
	bool	sq;

	i = -1;
	sq = true;
	dq = true;
	while (++i < len)
	{
		if (c->content[i] == 34 && sq)
			dq = !dq;
		if (c->content[i] == 39 && dq)
			sq = !sq;
	}
	return (sq + dq);
}

int	redirect_check(t_node *com)
{
	int	i;
	int	exit;

	i = -1;
	exit = 0;
	while (com->content[++i] && !exit)
	{
		while (is_open_quotes(com, i) < 2)
			i++;
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
