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

typedef struct sigaction	sigs;

enum	e_rror
{
	ERR_MALLOC = 1,
};

typedef struct s_minishell
{
	int		exit;
	char	*rec;
	char	**input;
	char	**path;
	char	**envp;
}	t_minishell;

void	ft_free_array(char **str);
int		ft_malloc_array(char ***str, char sep, char *line);
char	*add_backslash(char *str);
int		input_isnt_empty(char *str);

#endif
