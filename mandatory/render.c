/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:09:20 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/04 19:11:27 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>

int	ft_update(t_game *g)
{
	int		x;
	int		y;

	y = 0;
	g->n_frames++;
	ft_check_game(g);
	ft_update_score(g);
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

void	ft_update_score(t_game *g)
{
	char	*moves;

	moves = ft_itoa(g->n_moves);
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black_font, \
					g->width / 2 + 10, g->height + 7);
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black_font, \
					g->width / 2 + 42, g->height + 7);
	mlx_string_put(g->id, g->w_id, g->width / 2 + 14, g->height + 16, \
					0xFDD663, moves);
	free(moves);
}

void	ft_put_extras(t_game *g)
{
	mlx_string_put(g->id, g->w_id, g->width / 2 - 25, g->height + 15, \
		0xFDD663, "Moves:");
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.logo, \
		(g->width - 131) / 2, g->height + 20);
}

void	ft_redraw(t_vector old, t_vector nw, t_game *g, int hide)
{
	int	size;

	if (!hide)
	{
		mlx_destroy_image(g->id, g->sprites.pacman);
		if (g->pl && g->pl->dir == N)
			g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_up.xpm", &size, &size);
		if (g->pl && g->pl->dir == S)
			g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_down.xpm", &size, &size);
		if (g->pl && g->pl->dir == E)
			g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_right.xpm", &size, &size);
		if (g->pl && g->pl->dir == W)
			g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_left.xpm", &size, &size);
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
		nw.x * SIZE, nw.y * SIZE);
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacman, \
			nw.x * SIZE, nw.y * SIZE);
	}
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
		old.x * SIZE, old.y * SIZE);
}
