/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/30 10:43:26 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/player.h"

t_player	*ft_playerlist(char **map, t_lay lay)
{
	t_player	*players;
	int			i;
	int			x;
	int			y;

	y = 0;
	i = 0;
	players = malloc(sizeof(t_player) * (lay.nPlayers + lay.nGhosts + 1));
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
	player.score = 0;
	player.nLives = 3;
	player.nMoves = 0;
	player.dir = EAST;
	return (player);
}

t_vector	ft_newvector(int x, int y)
{
	t_vector	position;

	position.x = x;
	position.y = y;
	return (position);
}

int	move(char ***map, int d, t_player *p)
{
	int	i;

	i = 0;
	while (p[i].pos.x != -1 || p[i].pos.y != -1)
	{
		if (d == NORTH && ft_strchr("0C", map[0][p[i].pos.y + 1][p[i].pos.x]))
			return (ft_swap_tile(map, ft_newvector(p[i].pos.x, \
			p[i].pos.y), ft_newvector(p[i].pos.x, p[i].pos.y + 1), p));
		if (d == SOUTH && (map[0][p[i].pos.y - 1][p[i].pos.x] == '0' \
		|| map[0][p[i].pos.y - 1][p[i].pos.x] == 'C'))
			return (ft_swap_tile(map, ft_newvector(p[i].pos.x, \
			p[i].pos.y), ft_newvector(p[i].pos.x, p[i].pos.y + 1), p));
		if (d == EAST && (map[0][p[i].pos.y][p[i].pos.x + 1] == '0' \
		|| map[0][p[i].pos.y][p[i].pos.x + 1] == 'C'))
			return (ft_swap_tile(map, ft_newvector(p[i].pos.x, \
			p[i].pos.y), ft_newvector(p[i].pos.x - 1, p[i].pos.y), p));
		if (d == WEST && (map[0][p[i].pos.y][p[i].pos.x - 1] == '0' \
		|| map[0][p[i].pos.y][p[i].pos.x - 1] == 'C'))
			return (ft_swap_tile(map, ft_newvector(p[i].pos.x, \
			p[i].pos.y), ft_newvector(p[i].pos.x, p[i].pos.y + 1), p));
		i++;
	}
	return (0);
}

int	ft_swap_tile(char ***m, t_vector old, t_vector nw, t_player *p)
{
	char	temp;
	int		i;

	i = 0;
	temp = *m[nw.y][nw.x];
	*m[nw.y][nw.x] = *m[old.y][old.x];
	*m[old.y][old.x] = temp;
	while (p[i].pos.x != -1 && p[i].pos.y != -1)
	{
		if (p[i].pos.x == old.x && p[i].pos.y == old.y)
		{
			p[i].pos.x = nw.x;
			p[i].pos.y = nw.y;
		}
		i++;
	}
	return (1);
}
