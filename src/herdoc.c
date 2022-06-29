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

void	heredoc_part2(t_heredoc *her, t_node *com)
{
	int	fd;

	fd = open("/tmp/file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(her->input);
	remove_file(com, '<',  ft_strlen(her->delimiter));
	free(her->delimiter);
	redirect_check(com);
	dup2(fd, 0);
	close(fd);
	write(fd, her->container, ft_strlen(her->container));
    dup2(fd, 0);
    close(fd);
	free(her->container);
}

int	redirect_heredoc(t_node *com, int i)
{
	t_heredoc	    her;

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