#include "../include/minishell.h"

/*
 * Useful doc on exit codes and waitpid() macros :
 * https://tldp.org/LDP/abs/html/exitcodes.html
 * https://www.ibm.com/docs/en/ztpf/1.1.0.15?topic=apis-wtermsigdetermine-which-signal-caused-child-process-exit
*/

void	exit_code(int id)
{
	int	wstatus;

	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_ret = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
		g_ret = WTERMSIG(wstatus);
}

int	exit_extent(int code, int quote)
{
	free_var_init(com->sh, com);
	ft_free_list(com);
	if (quote == 0)
		ft_putstr_fd("bash: exit: too many arguments\n", out);
	if (quote == 1)
		ft_putstr_fd("bash: exit: numeric argument required\n", out);
	exit(code);
}

int	run_exit(t_node *com, int out)
{
	int	i;
	int	code;

	ft_putstr_fd("exit\n", out);
	if (com->args[1] == NULL)
		exit(0);
	if (com->args[1] != NULL && com->args[2] != NULL)
		exit_extent(128, 0);
	i = -1;
	if (com->args[1] != NULL && com->args[2] == NULL)
	{
		while (ft_isdigit(com->args[1][++i]) == 1)
			;
		if (com->args[1][i] != '\0')
			exit_extent(128, 1);
	}
	code = ft_atoi(com->args[1]);
	if (code >= 0 && code <= 255)
		exit(code);
	else
		exit(255);
	return (0);
}
