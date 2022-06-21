/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:30:17 by henkaoua          #+#    #+#             */
/*   Updated: 2022/06/18 10:30:19 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_dollar_txt(t_node *c, t_dollar *d, int j)
{
	char	*tmp;

	printf("before : %s\n", c->content);
	tmp = ft_substr(c->content, 0, d->i);
	tmp = ft_strjoin(tmp, c->content + (d->i + j));
	free(c->content);
	c->content = tmp;
	printf("after : %s\n", c->content);
}

int	if_quotes(t_node *c, t_dollar *d)
{
	int		i;
	bool	dq;
	bool	sq;

	i = -1;
	sq = true;
	dq = true;
	while (++i < d->i)
	{
		if (c->content[i] == 34 && sq)
			dq = !dq;
		if (c->content[i] == 39 && dq)
			sq = !sq;
	}
	return (sq);
}

int	dollar_sign_access(t_node *c, t_dollar *d, char **en)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (c->content[d->i + 1 + j] != 32 && c->content[d->i + 1 + j] != '\0')
		j++;
	if (c->content[d->i + j] == 34 && (c->content[d->i + j + 1] == '\0'
		|| c->content[d->i + j + 1] == 32))
		j--;
	i = -1;
	while (en[++i])
	{
		d->j = -1;
		while (en[i][++d->j] != '=')
			;
		if (!ft_strncmp(c->content + (d->i + 1), en[i], d->j) && if_quotes(c, d)
			&& !ft_strncmp(c->content + (d->i + 1), en[i], j) && if_quotes(c, d))
		{
			tmp = ft_strjoin(ft_substr(c->content, 0, d->i), en[i] + d->j + 1);
			tmp = ft_strjoin(tmp, c->content + (d->i + j + 1));
			free(c->content);
			c->content = tmp;
			break ;
		}
		/*else if (en[i + 1] == NULL)
			remove_dollar_txt(c, d, j);*/
	}
	return (-1);
}

void	dollar_sign_check(t_node *c, t_minishell *sh)
{
	t_dollar	d;

	d.i = -1;
	while (c->content[++d.i])
	{
		if (c->content[d.i] == '$')
			dollar_sign_access(c, &d, sh->envp);
	}
}
