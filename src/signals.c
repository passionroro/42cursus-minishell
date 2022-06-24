/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:08:39 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 19:08:40 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_ret = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signals(struct termios *save)
{
	struct termios	new;

	tcgetattr(STDIN_FILENO, save);
	new = *save;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
}
