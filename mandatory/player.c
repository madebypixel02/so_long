/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 17:00:16 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

t_player	*ft_playerlist(char **map, t_game *g)
{
	t_player	*players;
	int			i;
	int			x;
	int			y;

	y = 0;
	i = 0;
	players = malloc(sizeof(t_player) * (g->lay->n_pl + g->lay->n_gh + 1));
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				players[i++] = ft_newplayer(x, y);
			if (map[y][x] == 'G')
				players[i++] = ft_newplayer(x, y);
			x++;
		}
		y++;
	}
	players[i++] = ft_newplayer(-1, -1);
	return (players);
}

t_player	ft_newplayer(int x, int y)
{
	t_player	player;

	player.pos = ft_newvector(x, y);
	player.dir = ST;
	return (player);
}

int	ft_swap_tile(char ***m, t_vector old, t_vector nw, t_game *g)
{
	int		i;

	i = 0;
	if (m[0][nw.y][nw.x] == 'C')
		g->lay->n_collect--;
	if (m[0][nw.y][nw.x] == 'E')
	{
		if (!g->lay->n_collect)
			g->lay->n_pl--;
		return (1);
	}
	while (g->p[i].pos.x != -1)
	{
		if (g->p[i].pos.x == old.x && g->p[i].pos.y == old.y
			&& ft_strchr("CE0", m[0][nw.y][nw.x]))
			g->p[i].pos = ft_newvector(nw.x, nw.y);
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

	mlx_destroy_image(g->id, g->sprites.pacman);
	if (g->p[0].dir == N)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_up.xpm", &size, &size);
	if (g->p[0].dir == S)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_down.xpm", &size, &size);
	if (g->p[0].dir == E)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_right.xpm", &size, &size);
	if (g->p[0].dir == W)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_left.xpm", &size, &size);
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
		old.x * SIZE, old.y * SIZE + OFFSET);
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
		nw.x * SIZE, nw.y * SIZE + OFFSET);
	if (!hide)
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacman, \
			nw.x * SIZE, nw.y * SIZE + OFFSET);
}
