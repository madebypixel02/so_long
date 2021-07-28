/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:49:08 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 19:01:23 by aperez-b         ###   ########.fr       */
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
			color = (x * 255) / w + ((((w - x) * 255) / w) \
							<< 16) + (((y * 255) / h) << 8);
			mlx_pixel_put(mlx, win, x, y, color);
		}
	}
	return (0);
}

/*int	main(int argc, char **argv)
{
	int			fd;
	t_map_err	map_err;
	t_lay		lay;
	char		*map_str;
	char		**map;
	t_tile		**tilemap;
	void		*mlx;
	void		*mlx_win;

	map = NULL;
	mlx = mlx_init(); 
	map_str = NULL;
	ft_newlayout(&lay);
	ft_newmap_error(&map_err);
	if (argc != 2)
		error_msg_params("Invalid number of arguments!", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_msg_params("File not found!", NULL);
	if (ft_strrncmp(argv[1], ".ber", 4))
		error_msg_params("Invalid file type, use .ber!", NULL);
	ft_readlayout(fd, &map_err, &lay, &map_str);
	ft_print_map_error(&map_err, &map_str);
	map = ft_split(map_str, '\n');
	free(map_str);
	tilemap = ft_tilemap(map, lay);
	if (tilemap)
		free_tilemap(&tilemap, 1);
	mlx_win = mlx_new_window(mlx, 242, 242, "Test");
	color_map_1(mlx_win, 242, 242, mlx);
	mlx_clear_window(mlx, mlx_win);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	return (0);
}*/

int	main(int argc, char **argv)
{
}
