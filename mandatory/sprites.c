/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:02:26 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 11:41:49 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

t_sprite	ft_initsprites(t_game *g)
{
	int			size;

	size = SPRITE_SIZE;
	g->sprites.black = mlx_xpm_file_to_image(g->id,
			"sprites/Other/Walls/black.xpm", &size, &size);
	g->sprites.wall = mlx_xpm_file_to_image(g->id,
			"sprites/Other/Walls/wall.xpm", &size, &size);
	g->sprites.pacfood = mlx_xpm_file_to_image(g->id,
			"sprites/Other/Pacdots/pacdot_food.xpm", &size, &size);
	g->sprites.portal = mlx_xpm_file_to_image(g->id,
			"sprites/Other/Portal/portal.xpm", &size, &size);
	g->sprites.pacman = mlx_xpm_file_to_image(g->id,
			"sprites/Pac-Man/pac_closed.xpm", &size, &size);
	g->sprites.logo = mlx_xpm_file_to_image(g->id,
			"sprites/Other/Logo/logo.xpm", &size, &size);
	g->sprites.pac_dying = ft_load_pacdeath(g);
	return (g->sprites);
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
	mlx_destroy_image(game->id, game->sprites.logo);
	free_animation(game);
	return (0);
}

void	ft_print_static(t_game *g, int x, int y)
{
	if (g->map[y][x] == '1')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.wall, x * SPRITE_SIZE, y * SPRITE_SIZE + OFFSET);
	if (g->map[y][x] == 'E')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.portal, x * SPRITE_SIZE, y * SPRITE_SIZE + OFFSET);
	if (g->map[y][x] == 'C')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.pacfood, x * SPRITE_SIZE, y * SPRITE_SIZE + OFFSET);
	if (g->map[y][x] == 'P')
		mlx_put_image_to_window(g->id, g->window_id, g->sprites.pacman, x * SPRITE_SIZE, y * SPRITE_SIZE + OFFSET);
}

