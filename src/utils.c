#include "../include/minishell.h"

void	free_var_init(t_minishell *sh, t_node *com)
{
	ft_free_array(com->args);
	if (sh->path != NULL)
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

int	input_isnt_empty(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		if (env) 
        	ft_free_array(env);
		exit(printf("exit\n"));
	}
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
        || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i])
		return (1);
	else
		return (0);
}
