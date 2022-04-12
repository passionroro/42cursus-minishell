/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:44:05 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/12 22:13:00 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_real_command(t_minishell *sh, char *envp)
{
	int		i;
	int		ret;
	char	*tmp_path;

	if (ft_malloc_array(&sh->input, ' ', sh->rec))
		return (ERR_MALLOC);
	tmp_path = sh->path;
	if (!tmp_path)
		return (ERR_MALLOC);
	i = -1;
	ret = -1;
	while (sh->path[++i] && ret == -1)
	{
		tmp_path[i] = ft_strjoin(ft_strjoin(sh->path[i], "/"), sh->input[0]);
		if (!tmp_path[i])
			return (ERR_MALLOC);
		ret = access(tmp_path[i], F_OK);
	}
	if (ret == -1)
		return (-1); 
	execve(tmp_path[i - 1], &sh->input[0], envp);
	ft_free_array(sh->input);
	ft_free_array(tmp_path);
	return (0);
}

int	input_isnt_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i])
		return (1);
	else
		return (0);
}

//fix the signals "it worked but caused a segfault so fuck it, lets do it in the end"
//deal with the white spaces for the history "done"
//deal with Aliases and Special Characters "on the way sir"
//ft_split the input "done by you champ"

//WHAT I DID
// - put everything I could in a structure
// - created 2 functions in src/utils.c : 
// 		- ft_malloc_array will ft_split
// 		- ft_free_array will free this array.
// 		--this is in my opinion more clearer and safer
// - inside the function is_real_command() i changed the line 37
// 		- before : path[i] = ft_strjoin(ft_strjoin(sh->path[i], "/"), sh->input[0]);
// 		- now : tmp_path[i] = ft_strjoin(ft_strjoin(sh->path[i], "/"), sh->input[0]);
// 		--everything this does is using a TEMPORARY PATH because what we used before would suck
// 		--for example if you input "coucou" 3 times, a path would look like this : /usr/sbin/coucou/coucou/coucou
// 		--using a temporary path (tmp_path) fixes this issue.
// 		--pls don't mind if you have another idea to fix this issue <3

//WHAT I CHANGED
// - i made "sh.envp" to hold only the 12th line of the original envp so we have only one str with the PATH in it without the rest of the lines 
// - i added a simple functoin to check if the input is blank (white spaces). in this case we will jump to the free line (its ugly but i think its better if we dont send to exceve a malloced empty string.
//

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	t_minishell	sh;

	sh.envp = envp[12];
	if (ft_malloc_array(&sh.path, ':', sh.envp + 5))
		return (ERR_MALLOC);
	sh.exit = 1;
	while (sh.exit)
	{
		sh.rec = readline("[prompt]$ ");
		if (input_isnt_empty(sh.rec))
		{
			add_history(sh.rec);
			if (!is_real_command(&sh, envp[12]))
				printf("zsh: command not found: %s\n", sh.input[0]);
			sh.exit = ft_strncmp(sh.rec, "exit", sizeof(sh.rec));
		}
		free(sh.rec);
	}
	ft_free_array(sh.path);
	return (0);
}
