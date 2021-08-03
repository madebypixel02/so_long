/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:09:20 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 17:23:30 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

int	ft_update(t_game *g)
{
	int		x;
	int		y;

	y = 0;
	g->n_frames++;
	ft_check_game(g);
	if (g->redraw)
		ft_put_extras(g);
	while (g->map[y] && g->redraw)
	{
		x = 0;
		while (g->map[y][x])
		{
			ft_put_map(g, x, y);
			x++;
		}
		y++;
	}
	g->redraw = 0;
	return (0);
}

void	ft_put_extras(t_game *g)
{
	mlx_string_put(g->id, g->w_id, 10, 15, 0xFDD663, "Score: ");
	mlx_string_put(g->id, g->w_id, 10, 33, 0x87FFC5, "Moves: ");
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.logo, \
		(g->width - 131) / 2, g->height + 4);
}

void	ft_check_game(t_game *g)
{
	if (!(g->n_frames % g->g_rate) && !g->pac_dying)
		move(&g->map, g->p[0].dir, g);
	if (!g->lay->n_pl && !g->lay->n_collect)
	{
		if (!(g->n_frames % g->anim_rate))
			ft_anim_pacdeath(g);
		if (!g->pac_dying)
			end_game(g);
	}
}
