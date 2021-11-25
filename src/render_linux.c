/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:09:20 by aperez-b          #+#    #+#             */
/*   Updated: 2021/11/25 12:59:36 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <mlx.h>
#include <stdio.h>

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
			ft_redraw_exit(g, pl);
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

void	ft_redraw_exit(t_game *g, t_player *pl)
{
	if (pl->dir == N && g->map[pl->pos.y + 1][pl->pos.x] == 'E')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.portal, \
			pl->pos.x * SIZE, (pl->pos.y + 1) * SIZE);
	if (pl->dir == S && g->map[pl->pos.y - 1][pl->pos.x] == 'E')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.portal, \
			pl->pos.x * SIZE, (pl->pos.y - 1) * SIZE);
	if (pl->dir == E && g->map[pl->pos.y][pl->pos.x - 1] == 'E')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.portal, \
			(pl->pos.x - 1) * SIZE, pl->pos.y * SIZE);
	if (pl->dir == W && g->map[pl->pos.y][pl->pos.x + 1] == 'E')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.portal, \
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
