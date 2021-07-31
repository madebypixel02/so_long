/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:02:26 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 17:19:24 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

t_sprite	ft_initsprites(t_game *game)
{
	int			size;

	size = SPRITE_SIZE;
	game->sprites.black = mlx_xpm_file_to_image(game->id,
			"sprites/Other/Walls/black.xpm", &size, &size);
	game->sprites.wall = mlx_xpm_file_to_image(game->id,
			"sprites/Other/Walls/wall.xpm", &size, &size);
	game->sprites.pacfood = mlx_xpm_file_to_image(game->id,
			"sprites/Other/Pacdots/pacdot_food.xpm", &size, &size);
	game->sprites.portal = mlx_xpm_file_to_image(game->id,
			"sprites/Other/Portal/portal.xpm", &size, &size);
	game->sprites.pacman = mlx_xpm_file_to_image(game->id,
			"sprites/Pac-Man/pac_closed.xpm", &size, &size);
	return (game->sprites);
}

int	free_sprites(t_game *game, int only_pac)
{
	if (only_pac)
	{
		mlx_destroy_image(game->id, game->sprites.pacman);
		return (0);
	}
	mlx_destroy_image(game->id, game->sprites.black);
	mlx_destroy_image(game->id, game->sprites.wall);
	mlx_destroy_image(game->id, game->sprites.pacfood);
	mlx_destroy_image(game->id, game->sprites.portal);
	mlx_destroy_image(game->id, game->sprites.pacman);
	return (0);
}

void	ft_print_static(t_game *g, int x, int y)
{
	if (g->map[y][x] == '1')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.wall, x * SPRITE_SIZE, y * SPRITE_SIZE);
	if (g->map[y][x] == 'E')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.portal, x * SPRITE_SIZE, y * SPRITE_SIZE);
	if (g->map[y][x] == 'C')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.pacfood, x * SPRITE_SIZE, y * SPRITE_SIZE);
	if (g->map[y][x] == 'P')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.pacman, x * SPRITE_SIZE, y * SPRITE_SIZE);
}
