/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:06:25 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/26 17:26:36 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_open_quotes(t_node *c, int len)
{
	int		i;
	bool	dq;
	bool	sq;

	i = -1;
	sq = true;
	dq = true;
	while (++i < len)
	{
		if (c->content[i] == 34 && sq)
			dq = !dq;
		if (c->content[i] == 39 && dq)
			sq = !sq;
	}
	return (sq + dq);
}

char	*get_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
