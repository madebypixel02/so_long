/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:55:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/30 11:55:50 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include "../lib/player.h"
#include "../libft/lib/libft.h"
#include "../mlx.h"
#include <stdio.h>

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_Q || keycode == KEY_ESC)
		end_game(game);
	if (keycode == KEY_UP || keycode == KEY_W)
		move(&game->map, NORTH, game->players);
	if (keycode == KEY_DOWN || keycode == KEY_S)
		move(&game->map, SOUTH, game->players);
	if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(&game->map, EAST, game->players);
	if (keycode == KEY_LEFT || keycode == KEY_A)
		move(&game->map, WEST, game->players);
	return (0);
}

int	end_game(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	free(game->players);
	printf("%sGame Finished!%s\n", GREEN, DEFAULT);
	mlx_clear_window(game->id, game->window_id);
	mlx_destroy_window(game->id, game->window_id);
	//mlx_destroy_display(game->id);
	free(game->id);
	exit(0);
	return (0);
}

void	init_game(char **map, t_lay *lay)
{
	t_game	game;

	game = ft_newgame(map, *lay);
	mlx_loop_hook(game.id, ft_update, (void *)&game);
	mlx_hook(game.window_id, 17, 0, end_game, (void *)&game);
	mlx_key_hook(game.window_id, key_hook, (void *)&game);
	mlx_loop(game.id);
}

t_game	ft_newgame(char **map, t_lay lay)
{
	t_game	newgame;

	newgame.nFrames = 0;
	newgame.width = lay.nCol * SPRITE_SIZE;
	newgame.height = lay.nRow * SPRITE_SIZE;
	newgame.map = map;
	newgame.players = ft_playerlist(map, lay);
	newgame.id = mlx_init();
	newgame.window_id = mlx_new_window(newgame.id, \
	lay.nCol * SPRITE_SIZE, lay.nRow * SPRITE_SIZE, "Pac-Man Game");
	return (newgame);
}

int	ft_update(t_game *game)
{
	int		x;
	int		y;
	char	*c;

	y = 0;
	game->nFrames++;
	mlx_clear_window(game->id, game->window_id);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			c = ft_chartostr(game->map[y][x]);
			mlx_string_put(game->id, game->window_id, x * SPRITE_SIZE, \
			y * SPRITE_SIZE + 10, 0xFDD663, c);
			free(c);
			x++;
		}
		y++;
	}
	return (0);
}
