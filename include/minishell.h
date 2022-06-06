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

int g_ret;
void rl_replace_line (const char *text, int clear_undo);

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
	char        	*input;
	char        	**path;
	char	        **envp;
	int		        saved_fd[2];
}	t_minishell;

typedef struct s_clean_space
{
	int		i;
	int		l;
	int		b;
	int		e;
	char	*temp;
}	t_clean_space;


//s (simple) : number of simple quotes and their position
//d (double) : number of double quotes and their position
typedef struct	s_quotes
{
	int	s_num;
	int	d_num;
	int	*s_pos;
	int	*d_pos;
}	t_quotes;

t_node	*list_init(t_minishell *sh);
void	ft_signals(struct termios *save);
int	    input_isnt_empty(t_minishell *sh);
void	ft_free_array(char **str);
void	exit_code(int id);
int	    pipe_it_up(t_minishell *sh, t_node *com);
int	    var_init(t_minishell *sh, t_node *com);
int	    ft_malloc_array(char ***str, char sep, char *line);
void	redirect_check(t_node *com);
int	    pipe_it_up(t_minishell *sh, t_node *com);
char	**env_init(char **env);
char	*add_backslash(char *str);
int		is_built_in(char **env, char *str);
int		is_built_in2(char *str);
int		built_in_check(t_node *com);
void	free_var_init(t_minishell *sh, t_node *com);
int		run_unset(t_node *com);
int		run_export(t_node *com, int out);
int		run_echo(t_node *com, int out);
int		run_env(t_node *com, int out);
int		run_cd(t_node *com, int out);
int		run_pwd(char **env, int out);
int		run_exit(t_node *com, int out);
char	*get_path(char **env);
char	**env_create(t_node *com, int size);
char	*env_replace(t_node *com, int pos);
void	replace_pwd(t_node *com, char *dir);
void	replace_old_pwd(t_node *com);
void	ft_free_list(t_node *com);
void	clean_command(t_node *com, int *l, int *i);

#endif
