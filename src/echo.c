#include "../include/minishell.h"

int	run_echo(t_node *com, t_minishell *sh, int out)
{
	int	i;

	if (com->args[2] == NULL && !ft_strncmp(com->args[1], "-n\0", 3))
		return (1);
	if (com->args[1] == NULL)
	{
		ft_putchar_fd('\n', out);
		return (1);
	}
	i = 0;
	if (!ft_strncmp(com->args[1], "-n\0", 3))
		i++;
	while (com->args[++i])
	{
		ft_putstr_fd(com->args[i], out);
		if (com->args[i + 1] != NULL)
			ft_putchar_fd(' ', out);
	}
	if (ft_strncmp(com->args[1], "-n\0", 3))
		ft_putchar_fd('\n', out);
	g_ret = 0;
	return (1);
}
