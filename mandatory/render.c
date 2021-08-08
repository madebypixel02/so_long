/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:09:20 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/08 01:52:18 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>
#include <stdio.h>

int	ft_update(t_game *g)
{
	int		x;
	int		y;

	y = 0;
	g->n_frames++;
	ft_check_game(g);
	if (g->redraw)
	{
		ft_put_ghosts(g);
		ft_put_extras(g);
		ft_update_score(g);
		while (g->map[y])
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
	}
	return (0);
}

void	ft_put_extras(t_game *g)
{
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.logo, \
		(g->width - 131) / 2, g->height - 42);
}

void	ft_redraw(t_vector old, t_vector nw, t_game *g, int hide)
{
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
		old.x * SIZE, old.y * SIZE);
	if (!hide)
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
			nw.x * SIZE, nw.y * SIZE);
	if (!g->pac_dying)
		ft_put_pacman(g);
}
