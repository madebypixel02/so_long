/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:55:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 10:29:53 by aperez-b         ###   ########.fr       */
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
	printf("%d\n", ++game->nFrames);
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
	free_sprites(game);
	mlx_clear_window(game->id, game->window_id);
	mlx_destroy_window(game->id, game->window_id);
	mlx_destroy_display(game->id);
	free(game->id);
	exit(0);
	return (0);
}

void	init_game(char **map, t_lay *lay)
{
	t_game	game;

	game = ft_newgame(map, lay);
	mlx_loop_hook(game.id, ft_update, (void *)&game);
	mlx_hook(game.window_id, 17, 0, end_game, (void *)&game);
	mlx_key_hook(game.window_id, key_hook, (void *)&game);
	mlx_loop(game.id);
}

t_game	ft_newgame(char **map, t_lay *lay)
{
	t_game	newgame;

	newgame.nFrames = 0;
	newgame.width = lay->n_col * SPRITE_SIZE;
	newgame.height = lay->n_row * SPRITE_SIZE;
	newgame.lay = lay;
	newgame.map = map;
	newgame.players = ft_playerlist(map, lay);
	newgame.id = mlx_init();
	newgame.window_id = mlx_new_window(newgame.id, \
	lay->n_col * SPRITE_SIZE, lay->n_row * SPRITE_SIZE, "Pac-Man Game");
	newgame.sprites = ft_initsprites(&newgame);
	newgame.map_printed = 0;
	return (newgame);
}

int	ft_update(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	if (game->lay->n_collect == -1 && !game->lay->n_players)
		end_game(game);
	mlx_clear_window(game->id, game->window_id);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->id, game->window_id, game->sprites.wall, x * SPRITE_SIZE, y * SPRITE_SIZE);
			if (game->map[y][x] == 'E')
				mlx_put_image_to_window(game->id, game->window_id, game->sprites.portal, x * SPRITE_SIZE, y * SPRITE_SIZE);
			if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->id, game->window_id, game->sprites.pacman, x * SPRITE_SIZE, y * SPRITE_SIZE);
			if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->id, game->window_id, game->sprites.pacfood, x * SPRITE_SIZE, y * SPRITE_SIZE);
			x++;
		}
		y++;
	}
	game->map_printed = 1;
	return (0);
}
