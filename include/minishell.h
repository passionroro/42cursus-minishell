/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:44:48 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/28 16:58:15 by rohoarau         ###   ########.fr       */
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

int		g_ret;
void	rl_replace_line(const char *text, int clear_undo);

typedef struct s_node
{
	struct s_node		*next;
	struct s_node		*last;
	char				*content;
	char				**args;
	char				*path;
	int					id;
	struct s_minishell	*sh;
}	t_node;

typedef struct s_minishell
{
	char	*input;
	char	**path;
	char	**envp;
	int		nodes;
	int		saved_fd[2];
	int		pipe_fd[2];
	bool	even;
}	t_minishell;

typedef struct s_clean_space
{
	int		i;
	int		l;
	int		b;
	int		e;
	char	*temp;
}	t_clean_space;

typedef struct s_heredoc
{
	char	*input;
	char	*container;
	char	*delimiter;
}	t_heredoc;

typedef struct s_split
{
	int		i;
	int		r;
	int		k;
	char	tmp[1000];
	bool	even;
	char	q;
}	t_split;

typedef struct s_dollar
{
	int		i;
	int		j;
	int		q;
	int		n;
	char	*t;
}	t_dollar;

typedef struct s_redir
{
	int	i;
	int	exit;
}	t_redir;

t_node	*list_init(t_minishell *sh);
void	ft_signals(struct termios *save);
int		input_isnt_empty(char *str, char **env);
void	ft_free_array(char **str);
void	exit_code(t_node *com, int id);
int		pipe_it_up(t_minishell *sh, t_node *com);
int		var_init(t_minishell *sh, t_node *com);
int		ft_malloc_array(char ***str, char sep, char *line);
int		redirect_check(t_node *com);
int		pipe_it_up(t_minishell *sh, t_node *com);
char	**env_init(char **env);
char	*add_backslash(char *str);
int		is_built_in(char **env, char **args);
int		is_not_env(char *str);
int		built_in_exit(char *str);
int		built_in_check(t_node *com, t_minishell *sh);
int		free_var_init(t_minishell *sh, t_node *com, int ret);
int		run_unset(t_node *com, t_minishell *sh);
int		run_export(t_node *com, t_minishell *sh);
int		run_echo(t_node *com);
int		run_env(t_minishell *sh);
int		run_cd(t_node *com, t_minishell *sh);
int		run_pwd(char **env);
int		run_exit(t_node *com);
char	*get_path(char **env);
char	**env_create(t_node *com, int size, t_minishell *sh);
char	*env_replace(t_node *com, int pos, t_minishell *sh);
void	replace_pwd(t_node *com, char *dir, int code);
void	replace_old_pwd(t_node *com);
void	ft_free_list(t_node *com);
 void	remove_file(t_node *com, char c, int len);
int		ft_is_space(char c);
char	*write_file_name(char *str);
int		ft_strcmp(char *s1, char *s2);
int		write_error(char *s1, char *s2, char *s3, int ret);
int		redirect_heredoc(t_node *com, int i);
int		quote_is_closed(t_minishell *sh);
char	**ft_split_for_quotes(char *s, char c);
void	dollar_sign_check(t_node *com, t_minishell *sh);
void	signal_handler(int sig);
void	signal_process(int sig);
void	remove_quotes(t_node *com);
int		is_open_quotes(t_node *c, int len);

#endif
