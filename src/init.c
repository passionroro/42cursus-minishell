
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

void	erease_quote(t_node *com, int j, int i)
{
	char	*tmp;

	tmp = ft_substr(com->args[j], 0, i);
	tmp = ft_strjoin(tmp, com->args[j] + (i + 1));
	free(com->args[j]);
	com->args[j] = tmp;
}

void	remove_quotes(t_node *com)
{
	int		j;
	int		i;
	bool	sq;
	bool	dq;

	j = -1;
	sq = true;
	dq = true;
	while (com->args[++j])
	{
		i = -1;
		while (com->args[j][++i])
		{
			if (com->args[j][i] == 34 && sq)
			{
				dq = !dq;
				erease_quote(com, j, i);
			}
			if (com->args[j][i] == 39 && dq)
			{
				sq = !sq;
				erease_quote(com, j, i);
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
