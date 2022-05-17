/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:40:14 by rohoarau          #+#    #+#             */
/*   Updated: 2022/05/17 12:03:53 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	built_in_check(t_node *com)
{
	int	ret;

	ret = -1;
	if (ft_malloc_array(&com->args, ' ', com->content))
		return (ERR_MALLOC);
	dollar_sign_check(com);
	if (!ft_strncmp(com->args[0], "export\0", 7))
		ret = run_export(com);
	if (!ft_strncmp(com->args[0], "unset\0", 6))
		ret = run_unset(com);
	if (!ft_strncmp(com->args[0], "env\0", 4))
        ret = run_env(com);
	if (!ft_strncmp(com->args[0], "exit\0", 5))
		ret = 1;
	if (!ft_strncmp(com->args[0], "cd\0", 3))
		ret = run_cd(com);
	if (!ft_strncmp(com->args[0], "echo\0", 5))
		ret = run_echo(com);
	if (!ft_strncmp(com->args[0], "pwd\0", 4))
		ret = run_pwd(com->sh->envp);
	ft_free_array(com->args);
	return (ret);
}
