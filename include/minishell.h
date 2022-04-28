/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:50:37 by henkaoua          #+#    #+#             */
/*   Updated: 2022/04/28 15:12:50 by henkaoua         ###   ########.fr       */
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
	char			*path;
	int				fd[2];
	int				id;
}	t_node;

typedef struct s_minishell
{
	int		exit;
	int		id;
	char	*input;
	char	**commands;
	char	**path;
	char	**envp;
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
void	new_node(t_node *com, char *str);
t_node	*list_init(t_minishell *sh);
#endif
