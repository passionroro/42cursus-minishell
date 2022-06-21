/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:01:51 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/14 19:01:58 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_quotes(t_node *com)
{
	int		i;
	char	*tmp;

	i = -1;
	while (com->args[++i])
	{
		if (com->args[i][0] == 34 || com->args[i][0] == 39)
		{
			tmp = ft_substr(com->args[i], 1, ft_strlen(com->args[i]) - 2);
			free(com->args[i]);
			com->args[i] = tmp;
		}
	}
}

int	var_init(t_minishell *sh, t_node *com)
{
	dollar_sign_check(com, sh);
	com->args = ft_split_for_quotes(com->content, ' ');
	if (!com->args)
		return (-1);
	if (ft_malloc_array(&sh->path, ':', get_path(sh->envp)))
		if (is_built_in2(com->args[0]) != 1)
			return (-1);
	remove_quotes(com);
	return (0);
}
