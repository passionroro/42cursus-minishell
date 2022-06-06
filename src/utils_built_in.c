#include "../include/minishell.h"

void	free_list(t_node *com)
{
	while (com)
	{
		free(com->content);
		free(com);
		com = com->next;
	}
}

char	**env_init(char **env)
{
	char	**tmp;
	int		i;

	i = -1;
	while (env[++i])
		;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
			return (NULL);
	}
	tmp[i] = 0;
	return (tmp);
}
