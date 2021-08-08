/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:59:34 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/08 15:53:06 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>

void	*ft_chooseghcolor(t_game *g, int i, int dir)
{
	void	*sprite;
	char	*s;

	s = NULL;
	if (dir == N)
		s = ft_substr("sprites/Ghosts/R/ghost_up.xpm", 0, 29);
	else if (dir == S)
		s = ft_substr("sprites/Ghosts/R/ghost_down.xpm", 0, 31);
	else if (dir == E)
		s = ft_substr("sprites/Ghosts/R/ghost_right.xpm", 0, 32);
	else if (dir == W)
		s = ft_substr("sprites/Ghosts/R/ghost_left.xpm", 0, 31);
	if (i > 0)
		ft_memset(&s[15], COLORS[i % 7], 1);
	sprite = mlx_xpm_file_to_image(g->id, s, &dir, &dir);
	free(s);
	return (sprite);
}

void	ft_load_ghosts(t_game *g)
{
	t_player	*ghost;
	int			i;
	int			size;

	i = 0;
	ghost = g->gh;
	while (ghost)
	{
		ghost->sprites.up = ft_chooseghcolor(g, i, N);
		ghost->sprites.down = ft_chooseghcolor(g, i, S);
		ghost->sprites.right = ft_chooseghcolor(g, i, E);
		ghost->sprites.left = ft_chooseghcolor(g, i, W);
		ghost->sprites.panic1 = mlx_xpm_file_to_image(g->id, \
			"sprites/Ghosts/Panic/ghost_panic1.xpm", &size, &size);
		ghost->sprites.panic2 = mlx_xpm_file_to_image(g->id, \
			"sprites/Ghosts/Panic/ghost_panic2.xpm", &size, &size);
		ghost->sprites.black = mlx_xpm_file_to_image(g->id, \
			"sprites/Ghosts/black.xpm", &size, &size);
		ghost = ghost->next;
		i++;
	}
}

void	ft_put_ghosts(t_game *g)
{
	t_player	*ghost;

	ghost = g->gh;
	while (ghost)
	{
		if (ghost->dir == N && !g->panic_mode)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.up, \
				ghost->win_pos.x, ghost->win_pos.y);
		if (ghost->dir == S && !g->panic_mode)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.down, \
				ghost->win_pos.x, ghost->win_pos.y);
		if ((ghost->dir == E || ghost->dir == ST) && !g->panic_mode)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.right, \
				ghost->win_pos.x, ghost->win_pos.y);
		if (ghost->dir == W && !g->panic_mode)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.left, \
				ghost->win_pos.x, ghost->win_pos.y);
		else if (g->panic_mode && g->n_frames % g->g_rate < g->g_rate / 2)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.panic1, \
				ghost->win_pos.x, ghost->win_pos.y);
		else if (g->panic_mode)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.panic2, \
				ghost->win_pos.x, ghost->win_pos.y);
		ghost = ghost->next;
	}
}

void	ft_update_ghosts(t_game *g, t_player **pl)
{
	t_player	*ghost;
	t_player	*closest;
	int			dir;

	ghost = g->gh;
	while (ghost && !ghost->moving)
	{
		closest = ft_getnearestpac(g, ghost);
		dir = ft_choose_dir(g, ghost, closest);
		ghost->moving = 1;
		ft_move_ghost(dir, g, ghost, pl);
		ghost = ghost->next;
	}
}

void	ft_move_ghost(int d, t_game *g, t_player *gh, t_player **pl)
{
	t_vector	old;

	old = ft_newvector(gh->pos.x, gh->pos.y);
	ft_memset(&g->map[gh->pos.y][gh->pos.x], \
		'0', g->map[gh->pos.y][gh->pos.x] == 'G');
	if (d == N)
		gh->pos.y--;
	if (d == S)
		gh->pos.y++;
	if (d == E)
		gh->pos.x++;
	if (d == W)
		gh->pos.x--;
	gh->dir = d;
	if (g->map[gh->pos.y][gh->pos.x] == 'P')
	{
		gh->pos = old;
		g->pac_dying = 1;
	}
	mlx_put_image_to_window(g->id, g->w_id, gh->sprites.black, \
		old.x * SIZE, old.y * SIZE);
	if (g->map[old.y][old.x] == 'C')
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacfood, \
			old.x * SIZE, old.y * SIZE);
}
