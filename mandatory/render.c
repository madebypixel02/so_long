/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:09:20 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/14 11:00:57 by aperez-b         ###   ########.fr       */
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
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.logo, \
		(g->width - 131) / 2, g->height - 42);
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

void	ft_redraw_pac(t_game *g)
{
	t_player	*pl;

	pl = g->pl;
	while (pl)
	{
		if (pl->win_pos.x < pl->pos.x * SIZE && pl->moving)
			pl->win_pos.x++;
		if (pl->win_pos.x > pl->pos.x * SIZE && pl->moving)
			pl->win_pos.x--;
		if (pl->win_pos.y < pl->pos.y * SIZE && pl->moving)
			pl->win_pos.y++;
		if (pl->win_pos.y > pl->pos.y * SIZE && pl->moving)
			pl->win_pos.y--;
		if (pl->win_pos.x == pl->pos.x * SIZE && \
				pl->win_pos.y == pl->pos.y * SIZE)
			pl->moving = 0;
		pl = pl->next;
	}
	ft_put_pacman(g);
}

void	ft_redraw_gh(t_game *g)
{
	t_player	*pl;

	pl = g->gh;
	while (pl)
	{
		if (pl->win_pos.x < pl->pos.x * SIZE && pl->moving)
			pl->win_pos.x++;
		if (pl->win_pos.x > pl->pos.x * SIZE && pl->moving)
			pl->win_pos.x--;
		if (pl->win_pos.y < pl->pos.y * SIZE && pl->moving)
			pl->win_pos.y++;
		if (pl->win_pos.y > pl->pos.y * SIZE && pl->moving)
			pl->win_pos.y--;
		if (pl->win_pos.x == pl->pos.x * SIZE && \
				pl->win_pos.y == pl->pos.y * SIZE)
		{
			ft_redraw_pacfood(g, pl);
			pl->moving = 0;
		}
		pl = pl->next;
	}
	ft_put_ghosts(g);
}

void	ft_redraw_pacfood(t_game *g, t_player *pl)
{
	if (pl->dir == N && g->map[pl->pos.y + 1][pl->pos.x] == 'C')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacfood, \
			pl->pos.x * SIZE, (pl->pos.y + 1) * SIZE);
	if (pl->dir == S && g->map[pl->pos.y - 1][pl->pos.x] == 'C')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacfood, \
			pl->pos.x * SIZE, (pl->pos.y - 1) * SIZE);
	if (pl->dir == E && g->map[pl->pos.y][pl->pos.x - 1] == 'C')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacfood, \
			(pl->pos.x - 1) * SIZE, pl->pos.y * SIZE);
	if (pl->dir == W && g->map[pl->pos.y][pl->pos.x + 1] == 'C')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacfood, \
			(pl->pos.x + 1) * SIZE, pl->pos.y * SIZE);
}

void	ft_put_stopped(t_game *g, t_player *pl)
{
	if (pl->dir == N)
		mlx_put_image_to_window(g->id, g->w_id, pl->sprites.up_bak->content, \
			pl->pos.x * SIZE, pl->pos.y * SIZE);
	if (pl->dir == S)
		mlx_put_image_to_window(g->id, g->w_id, pl->sprites.down_bak->content, \
			pl->pos.x * SIZE, pl->pos.y * SIZE);
	if (pl->dir == E)
		mlx_put_image_to_window(g->id, g->w_id, pl->sprites.right_bak->content, \
			pl->pos.x * SIZE, pl->pos.y * SIZE);
	if (pl->dir == W)
		mlx_put_image_to_window(g->id, g->w_id, pl->sprites.left_bak->content, \
			pl->pos.x * SIZE, pl->pos.y * SIZE);
}
