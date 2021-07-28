/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:34:55 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 13:00:01 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

t_tile	ft_newtile(t_vector position, char content)
{
	t_tile	tile;

	tile.position = position;
	tile.content = content;
	if (tile.content == 'P')
		tile.player = ft_newplayer(1);
	else
		tile.player = ft_newplayer(-1);
	if (tile.content == 'B')
		tile.enemy = ft_newplayer(0);
	else
		tile.enemy = ft_newplayer(-1);
	return (tile);
}

t_tile	**ft_tilemap(char **map, t_lay lay)
{
	int		x;
	int		y;
	t_tile	**tilemap;

	tilemap = malloc(sizeof(t_tile *) * (lay.nRow + 1));
	if (!tilemap)
		return (error_msg_tile("Memory allocation error!", NULL));
	tilemap[lay.nRow] = NULL;
	y = 0;
	while (map[y])
	{
		x = 0;
		tilemap[y] = malloc(sizeof(t_tile) * (lay.nCol + 1));
		if (!tilemap[y])
			return (error_msg_tile("Memory allocation error!", &tilemap));
		while (map[y][x])
		{
			tilemap[y][x] = ft_newtile(ft_newvector(x, y), map[y][x]);
			x++;
		}
		tilemap[y][x] = ft_newtile(ft_newvector(x, y), '\0');
		y++;
	}
	free_matrix(&map, 0);
	return (tilemap);
}

void	free_tilemap(t_tile ***tilemap, int print)
{
	int	i;
	int	j;

	i = 0;
	while (tilemap[0][i])
	{
		j = 0;
		while (print && tilemap[0][i][j].content)
		{
			printf("%c", tilemap[0][i][j].content);
			j++;
		}
		if (print)
			printf("\n");
		free(tilemap[0][i]);
		i++;
	}
	free(tilemap[0]);
}
