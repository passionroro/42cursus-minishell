/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:38:50 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/17 14:52:51 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * 'env_init' : initializes OUR environement that will be used for builtins.
 * 'env_remove' : used when 'unset' is typed. 
 * 'env_replace' : used for 'export' in the case where the user exports an
 * environement variable that already exists (cf : 'export PATH=coucou')
 * 'env_create' : used for 'export' if the command doesn't exists.
 * 'free_list' : if 'free_list' is not explicit enough please type ':(){:|:&};:'
*/
void	free_list(t_node *com)
{
    ft_free_array(com->sh->commands);
	while (com)
	{
		free(com->content);
		free(com);
		com = com->next;
	}
}

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
