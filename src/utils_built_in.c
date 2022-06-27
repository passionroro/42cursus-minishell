/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:14:11 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/27 19:52:28 by rohoarau         ###   ########.fr       */
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

void	heredoc_part2(t_heredoc *her, t_node *com)
{
	free(her->input);
	free(her->delimiter);
	remove_file(com, '<', 0);
	redirect_check(com);
	printf("%s", her->container);
	free(her->container);
}

int	built_in_exit(char *str)
{
	if (!ft_strncmp(str, "export ", 7)
		|| !ft_strncmp(str, "unset ", 6)
		|| !ft_strncmp(str, "env ", 4)
		|| !ft_strncmp(str, "exit ", 5)
		|| !ft_strncmp(str, "cd ", 3)
		|| !ft_strncmp(str, "echo ", 5)
		|| !ft_strncmp(str, "pwd ", 4))
		return (1);
	return (0);
}

int	is_not_env(char *str)
{
	if (!ft_strncmp(str, "export\0", 7)
		|| !ft_strncmp(str, "unset\0", 6)
		|| !ft_strncmp(str, "exit\0", 5)
		|| !ft_strncmp(str, "cd\0", 3)
		|| !ft_strncmp(str, "echo\0", 5)
		|| !ft_strncmp(str, "pwd\0", 4))
		return (1);
	return (0);
}
