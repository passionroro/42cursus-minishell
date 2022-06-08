#include "../include/minishell.h"

/*check the return value of
- unknown command 
- ctrl+c alone + during pending process (ctrl+c during cat)
- if success, g_ret = 0
*/

void	exit_code(int id)
{
	int	wstatus;

	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_ret = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		g_ret = WTERMSIG(wstatus);
		if (g_ret != 131)
			g_ret += 127;
	}
}

int	run_exit(t_node *com, int out)
{
	int	i;

	ft_putstr_fd("exit\n", out);
	if (com->args[1] == NULL)
		exit(0);
	if (com->args[1] != NULL && com->args[2] != NULL)
		ft_putstr_fd("bash: exit: too many arguments\n", out);
	i = -1;
	if (com->args[1] != NULL && com->args[2] == NULL)
	{
		while (ft_isdigit(com->args[1][++i]) == 1)
			;
		if (com->args[1][i] != '\0')
			ft_putstr_fd("bash: exit: numeric argument required\n", out);
	}
	free_var_init(com->sh, com);
	ft_free_list(com);
	exit(0);
	return (0);
}