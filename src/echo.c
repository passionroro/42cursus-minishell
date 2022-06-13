#include "../include/minishell.h"

int	run_echo(t_node *com)
{
	int	i;
	if (com->args[2] == NULL && !ft_strncmp(com->args[1], "-n\0", 3))
		return (1);
	if (com->args[1] == NULL)
		return (printf("\n"));
	i = 0;
	if (!ft_strncmp(com->args[1], "-n\0", 3))
		i++;
	while (com->args[++i])
	{
		printf("%s", com->args[i]);
		if (com->args[i + 1] != NULL)
			printf(" ");
	}
	if (ft_strncmp(com->args[1], "-n\0", 3))
		printf("\n");
	g_ret = 0;
	return (1);
}
