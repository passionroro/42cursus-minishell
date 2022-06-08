#include "../include/minishell.h"

char	*get_home(char **env, int out)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "HOME=", 5))
            return (env[i] + 5);
	ft_putstr_fd("bash: cd: HOME not set\n", out);
	return (NULL);
}

int	old_pwd(char **env, t_node *com, int out)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			tmp = getcwd(NULL, 0);
			chdir(env[i] + 7);
			replace_pwd(com, env[i] + 7);
			ft_putstr_fd(env[i] + 7, out);
			ft_putchar_fd('\n', out);
			free(com->sh->envp[i]);
			com->sh->envp[i] = ft_strjoin(ft_strdup("OLDPWD="), tmp);
			free(tmp);
            return (1);
		}
	}
	ft_putstr_fd("bash: cd: OLDPWD not set\n", out);
	return (1);
}

int	run_cd(t_node *com, int out)
{
	if (com->args[1] == NULL || !ft_strncmp(com->args[1], "~\0", 2))
	{
		replace_old_pwd(com);
		replace_pwd(com, get_home(com->sh->envp, out));
		return (chdir(get_home(com->sh->envp, out)));
	}
	if (!ft_strncmp(com->args[1], "-\0", 2))
		return (old_pwd(com->sh->envp, com, out));
	chdir(com->args[1]);
	replace_old_pwd(com);
	replace_pwd(com, getcwd(NULL, 0));
	g_ret = 0;
	return (1);
}
