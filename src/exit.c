/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:58:36 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/26 15:33:54 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_code(t_node *com, int id, char **env)
{
	int	code;

	signal(SIGINT, signal_process);
	signal(SIGQUIT, signal_process);
	waitpid(id, &code, 0);
	if (is_built_in(env, com->args[0]) != 1)
	{
		if (WIFEXITED(code))
			g_ret = WEXITSTATUS(code);
		if (WIFSIGNALED(code))
			g_ret = WTERMSIG(code);
	}
}

int	exit_extent(t_node *com, int code, int quote)
{
	free_var_init(com->sh, com);
	ft_free_list(com, com->sh);
	if (quote == 0)
		write_error("bash: exit: too many arguments\n", NULL, NULL, 0);
	if (quote == 1)
		write_error("bash: exit: numeric argument required\n", NULL, NULL, 0);
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
