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

typedef struct sigaction	sigs;

enum	e_rror
{
	ERR_MALLOC = 1,
};

typedef struct s_node
{
	struct s_node	*next;
	char			*content;
	char			**input;
	char			*join;
	int				fd[2];
}	t_node;

typedef struct s_minishell
{
	int		exit;
	int		id;
	int		ret_val; //global
	char	*rec;
	char	**input;
	char	**path;
	char	**envp;
	char	*join;
}	t_minishell;

void	ft_free_array(char **str);
int		ft_malloc_array(char ***str, char sep, char *line);
char	*add_backslash(char *str);
int		input_isnt_empty(char *str);
int		print_error_message(int err_num);
char	*malloc_len(char *s, int len);
int		new_node(t_node *com, char *str,  int len, int ret);
#endif
