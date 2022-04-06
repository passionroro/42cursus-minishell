/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:36:59 by rohoarau          #+#    #+#             */
/*   Updated: 2022/04/06 16:33:28 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
static char *line_read = (char *)NULL;

char	*rl_gets(void)
{
	if (line_read)
	{
    	free (line_read);
    	line_read = (char *)NULL;
    }
	line_read = readline ("[prompt]$ ");
	if (line_read && *line_read)
    	add_history (line_read);
	return (line_read);
}


int	run_prompt(char *str, t_minishell sh)
{
	sh->prompt = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!sh->prompt)
		return (ERR_MALLOC);
}*/

void	signal_handler(int sig)
{
//	printf("signal: %d\n", sig);
	if (sig == 2)
	{
		write(1, "\n", 1);
		ft_putstr_fd("[prompt]$ ", 1);
	}
	if (sig == 3)
		return ;
}

int	main(int argc, char **envp)
{
	(void)envp;
	int			pid;
	int			exit;
	//t_minishell	sh;

	if (argc != 1)
		return (1);
	exit = 1;
	pid = getpid();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (exit)
	{
		//ft_putstr_fd("[prompt]$ ", 1);
		//char	line[128];
		char *line = NULL;
		printf("%s\n", line);
		//fgets(line, sizeof(line), stdin);
		exit = ft_strncmp(line, "exit\n", sizeof(line));
	}
	return (0);
}
