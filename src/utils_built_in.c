/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:14:11 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 19:14:12 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**env_init(char **env)
{
	char	**tmp;
	int		i;

	i = -1;
	while (env[++i])
		;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
			return (NULL);
	}
	tmp[i] = 0;
	return (tmp);
}

int	write_error(char *s1, char *s2, char *s3, int ret)
{
	ft_putstr_fd(s1, 2);
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		free(s2);
	}
	if (s3)
		ft_putstr_fd(s3, 2);
	return (ret);
}
