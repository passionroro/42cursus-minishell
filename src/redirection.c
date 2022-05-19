/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:50:26 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/19 22:36:24 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
void	redirect_delimiter(t_node *com, int *l, int *i)
{
}

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

void	redirect_append(t_node *com, int *l, int *i)
{
	int		s_stdout;
	int		fd;
	char	*file;

	com->redir = '>';
	com->append = true;
	s_stdout = dup(STDOUT_FILENO);
	if (com->args[*l][*i + 1] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 1);
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
	dup2(fd, STDOUT_FILENO);
	if (com->builtin == true)
		built_in_check(com);
	dup2(s_stdout, fd);
	close(s_stdout);
	free(file);
}

void	redirect_output(t_node *com, int *l, int *i)
{
	int		s_stdout;
	int		fd;
	char	*file;

	com->redir = '>';
	s_stdout = dup(STDOUT_FILENO);
	if (com->args[*l][*i + 1] == '\0')
		file = write_file_name(com->args[*l + 1]);
	else
		file = write_file_name(com->args[*l] + *i + 1);
	fd = open(file, O_WRONLY | O_CREAT, 0777);
	dup2(fd, STDOUT_FILENO);
	if (com->builtin == true)
		built_in_check(com);
	dup2(s_stdout, fd);
	close(s_stdout);
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
