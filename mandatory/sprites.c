/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:02:26 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 10:15:38 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

t_sprite	ft_initsprites(t_game *game)
{
	int			size;

	size = SPRITE_SIZE;
	game->sprites.black = mlx_xpm_file_to_image(game->id, "sprites/Other/Walls/black.xpm", &size, &size);
	game->sprites.wall = mlx_xpm_file_to_image(game->id, "sprites/Other/Walls/wall.xpm", &size, &size);
	game->sprites.pacfood = mlx_xpm_file_to_image(game->id, "sprites/Other/Pacdots/pacdot_food.xpm", &size, &size);
	game->sprites.portal = mlx_xpm_file_to_image(game->id, "sprites/Other/Portal/portal.xpm", &size, &size);
	game->sprites.pacman = mlx_xpm_file_to_image(game->id, "sprites/Pac-Man/pac_semi_right.xpm", &size, &size);
	return (game->sprites);
}

void	free_sprites(t_game *game)
{
	mlx_destroy_image(game->id, game->sprites.black);
	mlx_destroy_image(game->id, game->sprites.wall);
	mlx_destroy_image(game->id, game->sprites.pacfood);
	mlx_destroy_image(game->id, game->sprites.portal);
	mlx_destroy_image(game->id, game->sprites.pacman);
}
