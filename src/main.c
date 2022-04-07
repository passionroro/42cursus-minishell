/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:36:59 by rohoarau          #+#    #+#             */
/*   Updated: 2022/04/07 16:02:06 by henkaoua         ###   ########.fr       */
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
	struct termios	ter;

	if (sig == 2)
	{
		if (tcgetattr(STDIN_FILENO, &ter) != 0)
			perror("tcgetatt() error\n");
		else
		{
			write(1, "\n[prompt]$ ", 11);
			ter.c_lflag &= ~(ECHO | ECHONL | ICANON);
			tcsetattr(STDIN_FILENO, TCSANOW, &ter);
		}
	}
	if (sig == 3)
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argv;
	int				exit;
	t_minishell		sh;

	if (argc != 1)
		return (1);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	exit = 1;
	while (exit)
	{
		sh.line_read = readline("[prompt]$ ");
		if (sh.line_read)
			break ;
		add_history (sh.line_read);
		printf("line_read : %s\n", sh.line_read);
		exit = ft_strncmp(sh.line_read, "exit", sizeof(sh.line_read));
	}
	free(sh.line_read);
	sh.line_read = NULL;
	return (0);
}
