/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/25 15:57:51 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_for_backslash(t_minishell *sh, int ret)
{
	int	i;

	i = -1;
	if (sh->input[0][0] != '/')
	{
		sh->input[0] = add_backslash(sh->input[0]);
		if (!sh->input[0])
			return (ERR_MALLOC);
		while (sh->path[++i] && ret == -1)
		{
			sh->join = ft_strjoin(sh->path[i], sh->input[0]);
			if (!sh->join)
				return (ERR_MALLOC);
			ret = access(sh->join, F_OK);
			if (ret == -1)
				free(sh->join);
		}
	}
	else
	{
		sh->join = ft_strdup(sh->input[0]);
		ret = access(sh->join, F_OK);
	}
	return (ret);
}

int	is_real_command(t_minishell *sh)
{
	t_node	*com;
	int		i;
	int		l;

	i = -1;
	com = (t_node *)malloc(sizeof(t_node));
	while (sh->rec[++i] && sh->rec[i] != '|')
		l = i + 2;
	com->content = malloc_len(sh->rec, i);
	com->next = NULL;
	if (sh->rec[i] == '\0')
		i--;
	while (sh->rec[++i])
		if (sh->rec[i] == '|' && sh->rec[i + 1] == '\0')
			l = new_node(com, sh->rec + l, i - l, i + 1);
	/*if (ft_malloc_array(&sh->path, ':', sh->envp[12] + 5)
		|| ft_malloc_array(&sh->input, ' ', sh->rec))
		return (ERR_MALLOC);
	if (check_for_backslash(sh, -1) == -1)
	{
		printf("zsh: command not found: %s\n", sh->input[0]);
		ft_free_array(sh->input);
		return (-1);
	}
	return (execve(sh->join, &sh->input[0], sh->envp));*/
	return (0);
}

//check for $ sign and the following word
//deal with quotes: single quotes prints the word itself (so 'PATH' prints < PATH >), double quotes make evrything inside them one string (so ECHO "bla bla" prints < bla bla >).
//fix the signals

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	t_minishell	sh;

	sh.envp = envp;
	sh.exit = 0;
	while (!sh.exit)
	{
		sh.rec = readline("[prompt]$ ");
		if (input_isnt_empty(sh.rec))
		{
			add_history(sh.rec);
			if (fork() == 0)
				sh.exit = is_real_command(&sh);
			else
				wait(NULL);
		}
		free(sh.rec);
	}
	return (0);
}
