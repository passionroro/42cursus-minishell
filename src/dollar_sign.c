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

int	if_quotes(t_node *c, t_dollar d)
{
	int		i;
	bool	dq;
	bool	sq;

	i = -1;
	sq = true;
	dq = true;
	while (++i < d.i)
	{
		if (c->content[i] == 34 && sq)
			dq = !dq;
		if (c->content[i] == 39 && dq)
			sq = !sq;
	}
	return (sq);
}

void	remove_dollar_txt(t_node *c, t_dollar d)
{
	char	*tmp;

	if (if_quotes(c, d) && c->content[d.i] == '$')
	{
		tmp = ft_substr(c->content, 0, d.i);
		if (c->content[d.i + d.q + 1] != '\0')
			tmp = ft_strjoin(tmp, c->content + (d.i + d.q + 1));
		else
			tmp = ft_strjoin(tmp, "\n");
		free(c->content);
		c->content = tmp;
	}
}

int	dollar_sign_access(t_node *c, t_dollar d, char **en)
{
	d.q = 0;
	while (c->content[d.i + 1 + d.q] != 32 && c->content[d.i + 1 + d.q] != '\0'
		&& c->content[d.i + 1 + d.q] != 34 && c->content[d.i + 1 + d.q] != 39)
		d.q++;
	d.n = -1;
	while (en[++d.n])
	{
		d.j = -1;
		while (en[d.n][++d.j] != '=')
			;
		if (!ft_strncmp(c->content + (d.i + 1), en[d.n], d.j) && if_quotes(c, d)
			&& !ft_strncmp(c->content + (d.i + 1), en[d.n], d.q))
		{
			d.t = ft_strjoin(ft_substr(c->content, 0, d.i), en[d.n] + d.j + 1);
			d.t = ft_strjoin(d.t, c->content + (d.i + d.q + 1));
			free(c->content);
			c->content = d.t;
			break ;
		}
		else if (en[d.n + 1] == NULL)
			remove_dollar_txt(c, d);
	}
	return (-1);
}

void	dollar_sign_check(t_node *c, t_minishell *sh)
{
	t_dollar	d;
	char		*itoa;

	d.i = -1;
	while (c->content[++d.i])
	{
		if (c->content[d.i] == '$')
		{
			if (c->content[d.i + 1] == '?' && if_quotes(c, d))
			{
				itoa = ft_itoa(g_ret);
				d.t = ft_strjoin(ft_strjoin(ft_substr(c->content, 0, d.i),\
				itoa), c->content + d.i + 2);
				free(itoa);
				free(c->content);
				c->content = ft_strdup(d.t);
				free(d.t);
			}
			dollar_sign_access(c, d, sh->envp);
		}
	}
}
