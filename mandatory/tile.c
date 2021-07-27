/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:34:55 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 20:05:46 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	ft_newtile(t_tile *tile, int x, int y, char content)
{
	tile->position.x = x;
	tile->position.y = y;
	tile->content = content;
}

t_tile	**ft_tilemap(char **map, t_lay lay)
{
	int		x;
	int		y;
	t_tile	**tilemap;

	y = 0;
	tilemap = malloc(sizeof(t_tile *) * lay.nRow + 1);
	if (!tilemap)
		error_msg("Memory Allocation Error!", RED, NULL);
	while (map[y])
	{
		x = 0;
		tilemap[y] = malloc(sizeof(t_tile) * (lay.nCol + 1));
		if (!tilemap[y])
			error_msg("Memory Allocation Error!", RED, NULL);
		while (map[y][x])
		{
			ft_newtile(&tilemap[y][x], x, y, map[y][x]);
			x++;
		}
		ft_newtile(&tilemap[y][x], -1, -1, '\0');
		y++;
	}
	tilemap[y] = NULL;
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
