/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:36 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/22 20:45:06 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_process(int sig)
{
	if (sig == SIGINT)
		write (1, "^C\n", 3);
	if (sig == SIGQUIT)
		write (1, "^\\Quit: 3\n", 10);
}

void	exit_code(int id)
{
	int	wstatus;

	signal(SIGINT, signal_process);
	signal(SIGQUIT, signal_process);
	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_ret = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
		g_ret = WTERMSIG(wstatus);
}

int	exit_extent(t_node *com, int code, int quote)
{
	free_var_init(com->sh, com);
	ft_free_list(com);
	if (quote == 0)
		printf("bash: exit: too many arguments\n");
	if (quote == 1)
		printf("bash: exit: numeric argument required\n");
	exit(code);
}

int	run_exit(t_node *com)
{
	int	i;
	int	code;

	printf("exit\n");
	if (com->args[1] == NULL)
		exit(0);
	if (com->args[1] != NULL && com->args[2] != NULL)
		exit_extent(com, 128, 0);
	i = -1;
	if (com->args[1] != NULL && com->args[2] == NULL)
	{
		while (ft_isdigit(com->args[1][++i]) == 1)
			;
		if (com->args[1][i] != '\0')
			exit_extent(com, 128, 1);
	}
	code = ft_atoi(com->args[1]);
	if (code >= 0 && code <= 255)
		exit(code);
	else
		exit(255);
	return (0);
}
