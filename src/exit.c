/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:36 by henkaoua          #+#    #+#             */
/*   Updated: 2022/07/01 09:37:41 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_code(t_node *com, int id)
{
	int	code;

	signal(SIGINT, signal_process);
	signal(SIGQUIT, signal_process);
	waitpid(id, &code, 0);
	if (built_in_exit(com->content) != 1)
	{
		if (WIFEXITED(code))
			g_ret = WEXITSTATUS(code);
		if (WIFSIGNALED(code))
			g_ret = WTERMSIG(code) + 128;
	}
}

int	exit_extent(t_node *com, int code, int quote, t_minishell *sh)
{
	free_var_init(sh, com, 0);
	ft_free_list(com);
	if (quote == 0)
		write_error("minishell: exit: too many arguments\n", NULL, NULL, 0);
	if (quote == 1)
		write_error("minishell: exit: numeric argument required\n", \
				NULL, NULL, 0);
	exit(code);
}

int	run_exit(t_node *com, t_minishell *sh)
{
	int	i;
	int	code;

	printf("exit\n");
	if (com->args[1] == NULL)
		exit(0);
	if (com->args[1] != NULL && com->args[2] != NULL)
		exit_extent(com, 128, 0, sh);
	i = -1;
	if (com->args[1] != NULL && com->args[2] == NULL)
	{
		while (ft_isdigit(com->args[1][++i]) == 1)
			;
		if (com->args[1][i] != '\0')
			exit_extent(com, 128, 1, sh);
	}
	code = ft_atoi(com->args[1]);
	if (code >= 0 && code <= 255)
		exit(code);
	else
		exit(255);
	return (0);
}
