/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/11 13:49:02 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == 2)
		write(1, "\n[prompt]$ ", 11);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	sigs	sa;
	char	*input;
	char	**path;
	int		exit;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	path = ft_split(envp[12] + 5, ':');
	if (!path)
		return (NULL);
	exit = 1;
	while (exit)
	{
		input = readline("[prompt]$");
		add_history(input);
		exit = ft_strncmp(input, "exit", sizeof(input));
		free(input);
	}
	//free
	return (0);
}
