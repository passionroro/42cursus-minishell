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
	//struct s_node	*com;
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

void	ft_signals(struct termios *save);
int	    input_isnt_empty(t_minishell *sh);
void	ft_free_array(char **str);
void	exit_code(int id);
int	    pipe_it_up(t_minishell *sh, t_node *com);
int	    var_init(t_minishell *sh, t_node *com);
int	    ft_malloc_array(char ***str, char sep, char *line);
void	redirect_check(t_node *com);
int	    pipe_it_up(t_minishell *sh, t_node *com);

#endif
