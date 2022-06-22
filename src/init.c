
#include "../include/minishell.h"

int	quote_is_closed(t_minishell *sh)
{
	int		i;
	char	c;

	i = -1;
	sh->even = true;
	while (sh->input[++i])
	{
		if (sh->input[i] == 34 || sh->input[i] == 39)
		{
			c = sh->input[i];
			sh->even = !sh->even;
			while (sh->input[++i] && sh->input[i] != c)
				;
			if (sh->input[i] == c)
				sh->even = !sh->even;
		}
	}
	if (!sh->even)
		write_error("Error : open quotes\n", NULL, NULL, -1);
	return (sh->even);
}

void	change_content(t_node *com)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup("");
	while (com->args[++i])
		tmp = ft_strjoin(ft_strjoin(tmp, " "), com->args[i]);
	free(com->content);
	com->content = ft_strdup(tmp);
	free(tmp);
}

void	remove_it_for_real(t_node *c, int j, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(c->args[j], 0, i);
	tmp2 = ft_substr(c->args[j] + (i + 1), 0, ft_strlen(c->args[j] + (i + 1)));
	tmp1 = ft_strjoin(tmp1, tmp2);
	free(tmp2);
	i = ft_strlen(tmp1);
	while (tmp1[--i] != 34 && tmp1[i] != 39)
		;
	free(c->args[j]);
	c->args[j] = ft_substr(tmp1, 0, i);
	tmp2 = ft_substr(tmp1 + (i + 1), 0, ft_strlen(tmp1 + (i + 1)));
	c->args[j] = ft_strjoin(c->args[j], tmp2);
	change_content(c);
	free(tmp1);
	free(tmp2);
}

void	remove_quotes(t_node *com)
{
	int		j;
	int		i;

	j = -1;
	while (com->args[++j])
	{
		i = -1;
		while (com->args[j][++i])
		{
			if (com->args[j][i] == 34 || com->args[j][i] == 39)
			{
				remove_it_for_real(com, j, i);
				break ;
			}
		}
	}
}

int	var_init(t_minishell *sh, t_node *com)
{
	dollar_sign_check(com, sh);
	com->args = ft_split_for_quotes(com->content, ' ');
	if (!com->args)
		return (-1);
	if (ft_malloc_array(&sh->path, ':', get_path(sh->envp)))
		if (is_built_in2(com->args[0]) != 1)
			return (-1);
	remove_quotes(com);
	return (0);
}
