#include "../include/minishell.h"

int	dollar_sign_access(char *str, char **env)
{
	int	i;
	int	j;

	j = -1;
	while (str[++j] != '$')
		;
	i = -1;
	while (env[++i])
		if (!ft_strncmp(str + j + 1, env[i], ft_strlen(str + j + 1)))
			return (i);
	return (0);
}

void	dollar_sign_check(t_node *com)
{
	int	pos;
	int	i;
	int	j;

	i = -1;
	while (com->args[++i])
	{
		if (com->args[i][0] == '$')
		{
			if (!ft_strncmp(com->args[i], "$?\0", 3))
			{
				free(com->args[i]);
				com->args[i] = ft_itoa(g_ret);
			}
			pos = dollar_sign_access(com->args[i], com->sh->envp);
			if (pos != 0)
			{
				j = -1;
				while (com->sh->envp[pos][++j] != '=')
					;
				free(com->args[i]);
				com->args[i] = ft_strdup(com->sh->envp[pos] + j + 1);
			}
		}
	}
}

void	remove_quotes(t_node *com, int *count, char c)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(com->content) + 1 - *count));
	i = -1;
	j = -1;
	while (com->content[++i])
		if (com->content[i] != c)
			tmp[++j] = com->content[i];
	tmp[++j] = 0;
	free(com->content);
	com->content = ft_strdup(tmp);
	ft_free_array(com->args);
	ft_malloc_array(&com->args, ' ', tmp);
	free(tmp);
	*count = 0;
}

int	*quote_pos(char *str, char c, int count)
{
	int	*tab;
	int	i;
	int	j;

	if (count == 0)
		return (NULL);
	tab = malloc(sizeof(int) * count);
	if (!tab)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] == c)
			tab[++j] = i;
	return (tab);
}

int	quote_count(char *str, char c)
{
	int	i;
	int count;

	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == c)
			count += 1;
	return (count);
}

void	remove_quote_position(t_node *com, int start, int end)
{
	int		i;
	int		j;
	char	*tmp;

	//printf("start: %d = {%c}\nend: %d = {%c}\n", start, com->content[start], end, com->content[end]);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(com->content) - 1));
	if (!tmp)
		return ;
	i = -1;
	j = -1;
	while (com->content[++i])
		if (i != start && i != end)
			tmp[++j] = com->content[i];
	tmp[++j] = 0;
	free(com->content);
	com->content = ft_strdup(tmp);
	ft_free_array(com->args);
	ft_malloc_array(&com->args, ' ', tmp);
	free(tmp);
}

int	single_inside_doubles(t_node *com, t_quotes *q)
{
	int	i;
	int	j;


	i = -1;
	printf("doubles ");
	while (++i < q->d_num)
		printf("%d\t", q->d_pos[i]);
	i = -1;
	printf("\nsingles ");
	while (++i < q->s_num)
		printf("%d\t", q->s_pos[i]);
	i = -1;
	j = 0;
	while (++i < q->d_num && j < q->s_num)
	{
		if (q->d_pos[i] < q->s_pos[j] && q->d_pos[i + 1] > q->s_pos[j]) //echo "'salut" = 'salut
		{
			remove_quote_position(com, q->d_pos[i], q->d_pos[i + 1]);
			j++;
			i = j;
		}
	}
	return (j);
}

void	quotes_conditions(t_node *com, t_quotes *q)
{
	if (q->s_num % 2 == 0)
		if (single_inside_doubles(com, q) == 0) //echo "'""'" : even single and double : single_inside_doubles
			return (remove_quotes(com, &q->s_num, '\'')); //remove single quotes
		//simply print what is inside the single quotes : don't remove double quotes nor dollar sign
	if (q->s_num % 2 != 0)
	{
		if (single_inside_doubles(com, q) == 0)
		{
			ft_putstr_fd("Please close the quotes.\n", 2);
			g_ret = 0;
		}
		return ;
		//please close the quotes
		//unless single quote in inside double quotes
	}
	/*if (q->d_num % 2 == 0)
		if (q->s_num % 2 == 0)
			single_inside_doubles(com, q);
		//print what's inside : "'coucou'" -> 'coucou'
		//dollar sign is removed
	}
	if (q->d_num % 2 != 0)
	{
		;//please close the quotes
		//unless double quote in inside single quotes
	}*/
}

int	quote_check(t_node *com)
{
	t_quotes	q;

	q.s_num = quote_count(com->content, '\'');
	if (q.s_num > 0)
		q.s_pos = quote_pos(com->content, '\'', q.s_num);
	q.d_num = quote_count(com->content, '"');
	if (q.d_num > 0)
		q.d_pos = quote_pos(com->content, '"', q.d_num);
	if (q.d_num == 0 && q.s_num == 0)
		return (-1);
	quotes_conditions(com, &q);
	return (0);
}

int	var_init(t_minishell *sh, t_node *com)
{
	if (ft_malloc_array(&com->args, ' ', com->content))
		return (-1);
	if (ft_malloc_array(&sh->path, ':', get_path(sh->envp)))
		if (is_built_in2(com->args[0]) != 1)
			return (-1);
	quote_check(com);
	return (0);
}
