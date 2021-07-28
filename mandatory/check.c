/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:45:11 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 19:47:07 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/check.h"

t_tile	**check_params(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
		error_msg_params("Invalid number of arguments!", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_msg_params("File not found!", NULL);
	if (ft_strrncmp(argv[1], ".ber", 4))
		error_msg_params("Invalid file type, use .ber!", NULL);
	return (check_map(fd));
}

t_tile	**check_map(int fd)
{
	char	*map_str;
	char	**map;
	t_err	map_err;
	t_lay	lay;
	t_tile	**tilemap;

	map_str = NULL;
	map_err = ft_newmap_error();
	lay = ft_newlayout();
	ft_readlayout(fd, &map_err, &lay, &map_str);
	ft_print_map_error(&map_err, &map_str);
	map = ft_split(map_str, '\n');
	free(map_str);
	if (!map)
		error_msg_params("Memory allocation error!", NULL);
	tilemap = ft_tilemap(map, lay);
	if (!tilemap)
		error_msg_params("Memory allocation error!", NULL);
	else
		free_tilemap(&tilemap, 1);
	return (tilemap);
}
