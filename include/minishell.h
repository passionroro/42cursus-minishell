/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:44:48 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/17 16:48:53 by rohoarau         ###   ########.fr       */
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
	int					fd[2];
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

t_node	*list_init(t_minishell *sh);
void	ft_signals(struct termios *save);
int		input_isnt_empty(char *str, char **env);
void	ft_free_array(char **str);
void	exit_code(int id);
int		pipe_it_up(t_minishell *sh, t_node *com);
int		var_init(t_minishell *sh, t_node *com);
int		ft_malloc_array(char ***str, char sep, char *line);
int		redirect_check(t_node *com);
int		pipe_it_up(t_minishell *sh, t_node *com);
char	**env_init(char **env);
char	*add_backslash(char *str);
int		is_built_in(char **env, char *str);
int		is_built_in2(char *str);
int		built_in_check(t_node *com);
void	free_var_init(t_minishell *sh, t_node *com);
int		run_unset(t_node *com);
int		run_export(t_node *com);
int		run_echo(t_node *com);
int		run_env(t_node *com);
int		run_cd(t_node *com);
int		run_pwd(char **env);
int		run_exit(t_node *com);
char	*get_path(char **env);
char	**env_create(t_node *com, int size);
char	*env_replace(t_node *com, int pos);
void	replace_pwd(t_node *com, char *dir, int code);
void	replace_old_pwd(t_node *com);
void	ft_free_list(t_node *com);
void	remove_file(t_node *com, char c);
int		ft_is_space(char c);
char	*write_file_name(char *str);
int		ft_strcmp(char *s1, char *s2);
int		write_error(char *s1, char *s2, char *s3, int ret);
void	heredoc_part2(t_heredoc *her, t_node *com);

#endif
