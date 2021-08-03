/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:13:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 20:04:23 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	ft_newdirection(t_game *g, int direction)
{
	t_player	*temp;

	temp = g->pl;
	printf("%d\n", g->n_moves++);
	while (temp)
	{
		temp->dir = direction;
		temp = temp->next;
	}
}

t_vector	ft_newvector(int x, int y)
{
	t_vector	position;

	position.x = x;
	position.y = y;
	return (position);
}

void	move(char ***m, int d, t_game *g)
{
	t_player	*temp;

	temp = g->pl;
	while (temp)
	{
		if (d == N && ft_strchr("0CE", m[0][temp->pos.y - 1][temp->pos.x]))
			ft_swap_tile(m, ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x, temp->pos.y - 1), g);
		if (d == S && ft_strchr("0CE", m[0][temp->pos.y + 1][temp->pos.x]))
			ft_swap_tile(m, ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x, temp->pos.y + 1), g);
		if (d == E && ft_strchr("0CE", m[0][temp->pos.y][temp->pos.x + 1]))
			ft_swap_tile(m, ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x + 1, temp->pos.y), g);
		if (d == W && ft_strchr("0CE", m[0][temp->pos.y][temp->pos.x - 1]))
			ft_swap_tile(m, ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x - 1, temp->pos.y), g);
		temp = temp->next;
	}
}

int	ft_swap_tile(char ***m, t_vector old, t_vector nw, t_game *g)
{
	t_player	*temp;

	temp = g->pl;
	if (m[0][nw.y][nw.x] == 'C')
		g->lay->n_collect--;
	if (m[0][nw.y][nw.x] == 'E')
	{
		if (!g->lay->n_collect)
			g->lay->n_pl--;
		return (1);
	}
	while (temp)
	{
		if (temp->pos.x == old.x && temp->pos.y == old.y
			&& ft_strchr("CE0", m[0][nw.y][nw.x]))
			temp->pos = ft_newvector(nw.x, nw.y);
		temp = temp->next;
	}
	ft_memset(&m[0][nw.y][nw.x], m[0][old.y][old.x], 1);
	ft_memset(&m[0][old.y][old.x], '0', 1);
	ft_redraw(ft_newvector(old.x, old.y), ft_newvector(nw.x, nw.y), g, 0);
	return (1);
}
