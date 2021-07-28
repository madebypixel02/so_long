/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:49:08 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 21:18:30 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"
#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>

int	color_map_1(void *win, int w, int h, void *mlx)
{
	int	x;
	int	y;
	int	color;

	x = w;
	while (x--)
	{
		y = h;
		while (y--)
		{
			color = (x * 255) / w + ((((w - x) * 255) / w) << 16) + \
					(((y * 255) / h) << 8);
			mlx_pixel_put(mlx, win, x, y, color);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_tile	**tilemap;
	t_lay	lay;
	
	tilemap = check_params(argc, argv, &lay);
	init_game(tilemap, &lay);
	//free_tilemap(&tilemap, 1);
	return (0);
}
