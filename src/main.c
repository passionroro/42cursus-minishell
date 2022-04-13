/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/13 15:09:47 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*adding_backslash(char *str)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!ptr)
		return (NULL);
	ptr[0] = '/';
	i = -1;
	while (str[++i])
		ptr[i + 1] = str[i];
	ptr[i + 1] = '\0';
	free(str);
	return (ptr);
}

int	check_for_backslash(t_minishell *sh, int ret, char **join)
{
	int	i;

	i = -1;
	if (sh->input[0][0] != '/')
	{
		sh->input[0] = adding_backslash(sh->input[0]);
		if (!sh->input[0])
			return (ERR_MALLOC);
		while (sh->path[++i] && ret == -1)
		{
			*join = ft_strjoin(sh->path[i], sh->input[0]);
			if (!*join)
				return (ERR_MALLOC);
			ret = access(*join, F_OK);
			if (ret == -1)
				free(*join);
		}
	}
	else
	{
		*join = ft_strdup(sh->input[0]);
		ret = access(*join, F_OK);
	}
	return (ret);
}

int	is_real_command(t_minishell *sh)
{
	int	ret;
	char	*join;

	ret = -1;
	if (ft_malloc_array(&sh->path, ':', sh->envp[12] + 5))
		return (ERR_MALLOC);
	if (ft_malloc_array(&sh->input, ' ', sh->rec))
		return (ERR_MALLOC);
	ret = check_for_backslash(sh, ret, &join);
	if (ret == -1)
		return (-1);
	execve(join, &sh->input[0], sh->envp);
	ft_free_array(sh->path);
	ft_free_array(sh->input);
	free(join);
	return (0);
}

//fix the signals
//deal with the white spaces for the history
//deal with Aliases and Special Characters
//ft_split the input

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	t_minishell	sh;

	sh.envp = envp;
	sh.exit = 1;
	while (sh.exit)
	{
		sh.rec = readline("[prompt]$ ");
		if (sh.rec == NULL)
			break ;
		add_history(sh.rec);
		if (is_real_command(&sh))
			printf("zsh: command not found: %s\n", sh.rec);
		sh.exit = ft_strncmp(sh.rec, "exit", sizeof(sh.rec));
		free(sh.rec);
	}
	return (0);
}
