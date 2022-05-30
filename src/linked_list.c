#include "../include/minishell.h"

char	**ft_clean_space(char **str)
{
	t_clean_space	cs;

	cs.i = -1;
	while (str[++cs.i])
	{
		cs.b = 0;
		while (str[cs.i][cs.b] == ' ')
			cs.b++;
		cs.e = 0;
		while (str[cs.i][cs.e])
			cs.e++;
		while (str[cs.i][--cs.e] == ' ')
			;
        cs.temp = ft_strdup(str[cs.i]);
        free(str[cs.i]);
		str[cs.i] = (char *)malloc(sizeof(char) * (cs.e - cs.b) + 2);
		cs.l = -1;
		while (cs.b <= cs.e)
		{
			str[cs.i][++cs.l] = cs.temp[cs.b];
			cs.b++;
		}
		str[cs.i][++cs.l] = '\0';
		free(cs.temp);
	}
	return (str);
}

void ft_free_list(t_node *com)
{
	t_node	*tmp;

	while (com)
	{
		tmp = com;
		com = com->next;
		free(tmp);
	}
}

void	new_node(t_node *com, char *str, t_minishell *sh)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->content = str;
	new->next = NULL;
	while (com->next != NULL)
		com = com->next;
	new->last = com;
	com->next = new;
	com->sh = sh;
 	com->fd[0] = -1;
	com->fd[1] = -1;
}

t_node	*list_init(t_minishell *sh)
{
	t_node	*com;
	char	**commands;
	int		i;

	commands = ft_split(sh->input, '|'); //be  careful with free
	commands = ft_clean_space(commands);
	com = (t_node *)malloc(sizeof(t_node));
	com->content = commands[0];
	com->next = NULL;
	com->last = NULL;
	com->sh = sh;
    com->fd[0] = -1;
	com->fd[1] = -1;
	i = 0;
	while (commands[++i])
		new_node(com, commands[i], sh);
	ft_free_array(commands);
	return (com);
}