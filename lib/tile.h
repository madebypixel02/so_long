/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:32:49 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 19:58:03 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_H

# define TILE_H

# include "map.h"
# include "vector.h"

typedef struct s_tile
{
	t_vector	position;
	char		content;
}				t_tile;

void	ft_newtile(t_tile *tile, int x, int y, char content);
t_tile	**ft_tilemap(char **map, t_lay lay);
void	free_tilemap(t_tile ***tilemap, int print);

#endif
