/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:13:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 17:00:03 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	ft_newdirection(t_game *g, int direction)
{
	int	i;

	i = 0;
	printf("%d\n", g->n_moves++);
	while (g->p[i].pos.x != -1 && g->p[i].pos.y != -1)
	{
		g->p[i].dir = direction;
		i++;
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
	int	i;

	i = 0;
	while (g->p[i].pos.x != -1 || g->p[i].pos.y != -1)
	{
		if (d == N && ft_strchr("0CE", m[0][g->p[i].pos.y - 1][g->p[i].pos.x]))
			ft_swap_tile(m, ft_newvector(g->p[i].pos.x, g->p[i].pos.y), \
				ft_newvector(g->p[i].pos.x, g->p[i].pos.y - 1), g);
		if (d == S && ft_strchr("0CE", m[0][g->p[i].pos.y + 1][g->p[i].pos.x]))
			ft_swap_tile(m, ft_newvector(g->p[i].pos.x, g->p[i].pos.y), \
				ft_newvector(g->p[i].pos.x, g->p[i].pos.y + 1), g);
		if (d == E && ft_strchr("0CE", m[0][g->p[i].pos.y][g->p[i].pos.x + 1]))
			ft_swap_tile(m, ft_newvector(g->p[i].pos.x, g->p[i].pos.y), \
				ft_newvector(g->p[i].pos.x + 1, g->p[i].pos.y), g);
		if (d == W && ft_strchr("0CE", m[0][g->p[i].pos.y][g->p[i].pos.x - 1]))
			ft_swap_tile(m, ft_newvector(g->p[i].pos.x, g->p[i].pos.y), \
				ft_newvector(g->p[i].pos.x - 1, g->p[i].pos.y), g);
		i++;
	}
}
