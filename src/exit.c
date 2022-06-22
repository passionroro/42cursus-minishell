
#include "../include/minishell.h"

void	exit_code(int id)
{
	int	wstatus;

	signal(SIGINT, signal_process);
	signal(SIGQUIT, signal_process);
	waitpid(id, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_ret = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
		g_ret = WTERMSIG(wstatus);
}

int	exit_extent(t_node *com, int code, int quote)
{
	free_var_init(com->sh, com);
	ft_free_list(com);
	if (quote == 0)
		write_error("bash: exit: too many arguments\n", NULL, NULL, 0);
	if (quote == 1)
		write_error("bash: exit: numeric argument required\n", NULL, NULL, 0);
	exit(code);
}

int	run_exit(t_node *com)
{
	int	i;
	int	code;

	printf("exit\n");
	if (com->args[1] == NULL)
		exit(0);
	if (com->args[1] != NULL && com->args[2] != NULL)
		exit_extent(com, 128, 0);
	i = -1;
	if (com->args[1] != NULL && com->args[2] == NULL)
	{
		while (ft_isdigit(com->args[1][++i]) == 1)
			;
		if (com->args[1][i] != '\0')
			exit_extent(com, 128, 1);
	}
	code = ft_atoi(com->args[1]);
	if (code >= 0 && code <= 255)
		exit(code);
	else
		exit(255);
	return (0);
}
