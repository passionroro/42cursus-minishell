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

int	redirect_check(t_node *com, t_minishell *sh);

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
	remove_file(com, '<', ft_strlen(file));
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
	remove_file(com, '>', ft_strlen(file));
	free(file);
	return (0);
}

void	first_char_checker(t_node *com, t_minishell *sh)
{
	if (com->content[0] == '<')
	{
		if (com->content[1] == '<')
			redirect_heredoc(com, 0, sh);
		else
			redirect_input(com, 0);
	}
	if (com->content[0] == '>')
	{
		if (com->content[1] == '>')
			redirect_append(com, 0);
		else
			redirect_output(com, 0);
	}
}

void	too_many_lines(t_node *com, t_redir *r)
{
	if (com->content[r->i + 1] == '>')
		r->exit = redirect_append(com, r->i);
	else
		r->exit = redirect_output(com, r->i);
	r->i -= 1;
}

int	redirect_check(t_node *com, t_minishell *sh)
{
	t_redir	r;

	r.i = -1;
	r.exit = 0;
	first_char_checker(com, sh);
	while (com->content[++r.i] && !r.exit)
	{
		while (is_open_quotes(com, r.i + 1) < 2)
			r.i++;
		if (com->content[r.i] == '<')
		{
			if (com->content[r.i + 1] == '<')
				r.exit = redirect_heredoc(com, r.i, sh);
			else
				r.exit = redirect_input(com, r.i);
			r.i -= 1;
		}
		else if (com->content[r.i] == '>')
			too_many_lines(com, &r);
	}
	return (r.exit);
}
