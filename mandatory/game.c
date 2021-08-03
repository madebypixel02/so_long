/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:55:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 09:28:16 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

int	key_hook(int key, t_game *game)
{
	if (key == KEY_Q || key == KEY_ESC)
		end_game(game);
	if ((key == KEY_UP || key == KEY_W) && game->p[0].dir != N)
	{
		ft_newdirection(game, N);
		move(&game->map, N, game);
	}
	if ((key == KEY_DOWN || key == KEY_S) && game->p[0].dir != S)
	{
		ft_newdirection(game, S);
		move(&game->map, S, game);
	}
	if ((key == KEY_RIGHT || key == KEY_D) && game->p[0].dir != E)
	{
		ft_newdirection(game, E);
		move(&game->map, E, game);
	}
	if ((key == KEY_LEFT || key == KEY_A) && game->p[0].dir != W)
	{
		ft_newdirection(game, W);
		move(&game->map, W, game);
	}
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
	free(game->p);
	printf("%sGame Finished!%s\n", GREEN, DEFAULT);
	free_sprites(game, 0);
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

	game = ft_newgame(map, lay);
	mlx_loop_hook(game.id, ft_update, (void *)&game);
	mlx_hook(game.window_id, 17, 0, end_game, (void *)&game);
	mlx_key_hook(game.window_id, key_hook, (void *)&game);
	mlx_loop(game.id);
}

t_game	ft_newgame(char **map, t_lay *lay)
{
	t_game	newgame;

	newgame.n_frames = 1;
	newgame.n_moves = 1;
	newgame.width = lay->n_col * SPRITE_SIZE;
	newgame.height = lay->n_row * SPRITE_SIZE + OFFSET;
	newgame.lay = lay;
	newgame.map = map;
	newgame.id = mlx_init();
	newgame.window_id = mlx_new_window(newgame.id, \
	lay->n_col * SPRITE_SIZE, lay->n_row * SPRITE_SIZE + 100, "Pac-Man Game");
	newgame.sprites = ft_initsprites(&newgame);
	newgame.p = ft_playerlist(map, &newgame);
	newgame.redraw = 1;
	return (newgame);
}

int	ft_update(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	game->n_frames++;
	if (!(game->n_frames % 8000))
		move(&game->map, game->p[0].dir, game);
	if (!game->lay->n_players && !game->lay->n_collect)
		end_game(game);
	while (game->map[y] && game->redraw)
	{
		x = 0;
		while (game->map[y][x])
		{
			ft_print_static(game, x, y);
			x++;
		}
		y++;
		mlx_string_put(game->id, game->window_id, 10, 15, 0xFDD663, "Score: ");
		mlx_string_put(game->id, game->window_id, 10, 33, 0x87FFC5, "Moves: ");
		mlx_put_image_to_window(game->id, game->window_id, game->sprites.logo, (game->width - 131) / 2, game->height + 4);
	}
	game->redraw = 0;
	return (0);
}
