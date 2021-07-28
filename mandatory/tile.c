/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:34:55 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 10:43:03 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

t_tile	ft_newtile(t_vector position, char content)
{
	t_tile tile;

	if (!content)
	{
		tile.position = position;
		tile.content = '\0';
	}
	else
	{
		tile.position = position;
		tile.content = content;
	}
	//printf("(%d, %d)\n", tile.position.x, tile.position.y);
	return (tile);
}

t_tile	**ft_tilemap(char **map, t_lay lay)
{
	int		x;
	int		y;
	t_tile	**tilemap;

	tilemap = malloc(sizeof(t_tile *) * (lay.nRow + 1));
	if (!tilemap)
	{
		error_msg("Memory allocation error!", NULL, NULL);
		return (NULL);
	}
	y = 0;
	while (map[y])
	{
		x = 0;
		tilemap[y] = malloc(sizeof(t_tile) * (lay.nCol + 1));
		if (!tilemap[y])
		{
			error_msg("Memory allocation error!", NULL, &tilemap);
			return (NULL);
		}
		while (map[y][x])
		{
			tilemap[y][x] = ft_newtile(ft_newvector(x, y), map[y][x]);
			x++;
		}
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
