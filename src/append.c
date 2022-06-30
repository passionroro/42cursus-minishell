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
	remove_file(com, '>', ft_strlen(file));
	free(file);
	return (0);
}
