/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:50:37 by henkaoua          #+#    #+#             */
/*   Updated: 2022/05/17 14:55:11 by rohoarau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <string.h>

int	ret_val;
void rl_replace_line (const char *text, int clear_undo);

enum	e_rror
{
	ERR_MALLOC = 1,
};

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*last;
	char			*content; //entire pipe command
	char			**args; //command devided to words
	char			*path;	//right path to the command
	int				fd[2];
	int				id;
	struct s_minishell	*sh;
}	t_node;

typedef struct s_minishell
{
	int		exit;
	int		id;
	char	*input;
	char	**commands;
	char	**path;
	char	**envp;
	struct s_node	*com;
}	t_minishell;

typedef struct s_clean_space
{
	int		i;
	int		l;
	int		b;
	int		e;
	char	*temp;
}	t_clean_space;

void	print_list(t_node *list);
void	ft_free_array(char **str);
int		ft_malloc_array(char ***str, char sep, char *line);
char	*add_backslash(char *str);
int		input_isnt_empty(char *str);
int		print_error_message(int err_num);
char	*malloc_len(char *s, int len);
void	new_node(t_node *com, char *str, t_minishell *sh);
t_node	*list_init(t_minishell *sh);
void	ft_free_list(t_node *com);
int		built_in_check(t_node *com);
char	*env_replace(t_node *com, int pos);
char	**env_create(t_node *com, int size);
char	**env_remove(char **str, int pos);
char	**env_init(char **env);
void	print_export(char **tab);
int		print_sort_env(char **tab);
int		run_unset(t_node *com);
int		run_export(t_node *com);
int		run_echo(t_node *com);
int		run_env(t_node *com);
int		run_cd(t_node *com);
int		run_pwd(char **env);
int		get_pwd_pos(char **env);
void	replace_pwd(t_node *com, char *dir);
void	dollar_sign_check(t_node *com);

#endif
