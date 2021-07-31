/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 17:29:34 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>
#include <stdlib.h>

void	ft_delete_player(t_game *g, int n)
{
	int	i;

	i = 0;
	while (g->p[i].pos.x == -1)
	{
		i++;
	}
}

t_player	*ft_playerlist(char **map, t_game *g)
{
	t_player	*players;
	int			i;
	int			x;
	int			y;

	y = 0;
	i = 0;
	players = malloc(sizeof(t_player) * (g->lay->n_players + g->lay->n_ghosts + 1));
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				players[i++] = ft_newplayer(1, x, y);
			if (map[y][x] == 'G')
				players[i++] = ft_newplayer(0, x, y);
			x++;
		}
		y++;
	}
	players[i++] = ft_newplayer(0, -1, -1);
	return (players);
}

t_player	ft_newplayer(int is_main_player, int x, int y)
{
	t_player	player;

	player.pos = ft_newvector(x, y);
	player.is_main_player = is_main_player;
	player.dir = ST;
	return (player);
}

t_vector	ft_newvector(int x, int y)
{
	t_vector	position;

	position.x = x;
	position.y = y;
	return (position);
}

void	move(char ***map, int d, t_game *g)
{
	int	i;

	i = 0;
	while (g->p[i].pos.x != -1 || g->p[i].pos.y != -1)
	{
		if (d == N && ft_strchr("0CE", map[0][g->p[i].pos.y - 1][g->p[i].pos.x]))
			ft_swap_tile(map, ft_newvector(g->p[i].pos.x, g->p[i].pos.y),
			ft_newvector(g->p[i].pos.x, g->p[i].pos.y - 1), g);
		if (d == S  && ft_strchr("0CE", map[0][g->p[i].pos.y + 1][g->p[i].pos.x]))
			ft_swap_tile(map, ft_newvector(g->p[i].pos.x, g->p[i].pos.y),
			ft_newvector(g->p[i].pos.x, g->p[i].pos.y + 1), g);
		if (d == E && ft_strchr("0CE", map[0][g->p[i].pos.y][g->p[i].pos.x + 1]))
			ft_swap_tile(map, ft_newvector(g->p[i].pos.x, g->p[i].pos.y),
			ft_newvector(g->p[i].pos.x + 1, g->p[i].pos.y), g);
		if (d == W && ft_strchr("0CE", map[0][g->p[i].pos.y][g->p[i].pos.x - 1]))
			ft_swap_tile(map, ft_newvector(g->p[i].pos.x, g->p[i].pos.y),
			ft_newvector(g->p[i].pos.x - 1, g->p[i].pos.y), g);
		i++;
	}
}

int	ft_swap_tile(char ***m, t_vector old, t_vector nw, t_game *g)
{
	int		i;

	i = 0;
	if (m[0][nw.y][nw.x] == 'C')
		g->lay->n_collect--;
	if (m[0][nw.y][nw.x] == 'E')
	{
		if (g->lay->n_collect)
			return (1);
		return (ft_delete_player(g, i));
	}
	while (g->p[i].pos.x != -1)
	{
		if (g->p[i].pos.x == old.x && g->p[i].pos.y == old.y
			&& ft_strchr("C0", m[0][nw.y][nw.x]))
			g->p[i].pos = ft_newvector(nw.x, nw.y);
		if (g->p[i].pos.x == old.x && g->p[i].pos.y == old.y
			&& m[0][nw.y][nw.x] == 'E')
			g->p[i].pos = ft_newvector(0, 0);
		i++;
	}
	ft_memset(&m[0][nw.y][nw.x], m[0][old.y][old.x], 1);
	ft_memset(&m[0][old.y][old.x], '0', 1);
	ft_redraw(ft_newvector(old.x, old.y), ft_newvector(nw.x, nw.y), g, 0);
	return (1);
}

void	ft_redraw(t_vector old, t_vector nw, t_game *g, int hide)
{
	int	size;

	free_sprites(g, 1);
	if (g->p[0].dir == N)	
		g->sprites.pacman = mlx_xpm_file_to_image(g->id,
			"sprites/Pac-Man/pac_semi_up.xpm", &size, &size);
	if (g->p[0].dir == S)	
		g->sprites.pacman = mlx_xpm_file_to_image(g->id,
			"sprites/Pac-Man/pac_semi_down.xpm", &size, &size);
	if (g->p[0].dir == E)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id,
			"sprites/Pac-Man/pac_semi_right.xpm", &size, &size);
	if (g->p[0].dir == W)	
		g->sprites.pacman = mlx_xpm_file_to_image(g->id,
			"sprites/Pac-Man/pac_semi_left.xpm", &size, &size);
	mlx_put_image_to_window(g->id, g->window_id, g->sprites.black,
	old.x * SPRITE_SIZE, old.y * SPRITE_SIZE);
	if (!hide)
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.pacman,
	nw.x * SPRITE_SIZE, nw.y * SPRITE_SIZE);
}
