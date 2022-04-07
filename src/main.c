/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:36:59 by rohoarau          #+#    #+#             */
/*   Updated: 2022/04/06 23:49:42 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
int	run_prompt(char *str, t_minishell sh)
{
	sh->prompt = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!sh->prompt)
		return (ERR_MALLOC);
}*/

void	signal_handler(int sig)
{
	//t_minishell	sh;

	if (sig == 2)
		write(1, "\n[prompt]$ ", 11);
	if (sig == 3)
		return ;
		//sh.line_read = "\0";
}

int	main(int argc, char **envp)
{
	(void)envp;
	int			pid;
	int			exit;
	t_minishell	sh;

	if (argc != 1)
		return (1);
	exit = 1;
	pid = getpid();
	while (exit)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		sh.line_read = readline("[prompt]$ ");
		printf("line_read	%s\n", sh.line_read);
		exit = ft_strncmp(sh.line_read, "exit", sizeof(sh.line_read));
	}
	free(sh.line_read);
	return (0);
}
