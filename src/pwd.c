#include "../include/minishell.h"

int	get_pwd_pos(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PWD=", 4))
			return (i);
	return (-1);
}

void	replace_pwd(t_node *com, char *dir)
{
	int		pos;

	pos = get_pwd_pos(com->sh->envp);
	free(com->sh->envp[pos]);
	com->sh->envp[pos] = ft_strjoin(ft_strdup("PWD="), dir);
	if (!dir)
		free(dir);
}

int	get_old_pwd_pos(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			return (i);
	return (-1);
}

void	replace_old_pwd(t_node *com)
{
	char	*dir;
	int		old_pos;
	int		pwd_pos;

	pwd_pos = get_pwd_pos(com->sh->envp);
	old_pos = get_old_pwd_pos(com->sh->envp);
	if (pwd_pos == -1 || old_pos == -1)
		return ;
	dir = ft_strdup(com->sh->envp[pwd_pos] + 4);
	free(com->sh->envp[old_pos]);
	com->sh->envp[old_pos] = ft_strjoin(ft_strdup("OLDPWD="), dir);
	free(dir);
}

int	run_pwd(char **env, int out)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PWD=", 4))
			return (printf("%s\n", env[i] + 4));
	g_ret = 0;
	return (-1);
}
