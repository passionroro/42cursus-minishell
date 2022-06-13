#include "../include/minishell.h"

void	free_var_init(t_minishell *sh, t_node *com)
{
	ft_free_array(com->args);
	ft_free_array(sh->path);
}

int	ft_malloc_array(char ***str, char sep, char *line)
{
	*str = ft_split(line, sep);
	if (!*str)
		return (1);
	return (0);
}

void	ft_free_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*add_backslash(char *str)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!ptr)
		return (NULL);
	ptr[0] = '/';
	i = -1;
	while (str[++i])
		ptr[i + 1] = str[i];
	ptr[i + 1] = '\0';
	free(str);
	return (ptr);
}

int	input_isnt_empty(t_minishell *sh)
{
	int	i;

	i = 0;
	if (sh->input == NULL)
	{
		ft_putstr_fd("exit", 1);
        ft_free_array(sh->envp);
		exit(1);
	}
	while (sh->input[i] == 32 || sh->input[i] == '\t' || sh->input[i] == '\n'
        || sh->input[i] == '\v' || sh->input[i] == '\f'
        || sh->input[i] == '\r')
		i++;
	if (sh->input[i])
		return (1);
	else
		return (0);
}