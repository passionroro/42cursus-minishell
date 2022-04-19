/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/19 20:23:03 by henkaoua         ###   ########.fr       */
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
	if (ft_malloc_array(&sh->path, ':', sh->envp[12] + 5)
		|| ft_malloc_array(&sh->input, ' ', sh->rec))
		return (ERR_MALLOC);
	if (check_for_backslash(sh, -1) == -1)
	{
		printf("zsh: command not found: %s\n", sh->input[0]);
		//ft_free_array(sh->path);
// IDK why it says that << sh->path >> was freed before.
		ft_free_array(sh->input);
		return (-1);
	}
	return (execve(sh->join, &sh->input[0], sh->envp));
}

//fix the signals
//deal with Aliases and Special Characters

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
