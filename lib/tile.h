/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:32:49 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 18:46:24 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_H

# define TILE_H

# include "map.h"
# include "player.h"
# include "vector.h"

typedef struct s_tile
{
	t_vector	position;
	char		content;
	t_player	player;
	t_player	enemy;
}				t_tile;

t_tile	ft_newtile(t_vector position, char content);
t_tile	**ft_tilemap(char **map, t_lay lay);
void	free_tilemap(t_tile ***tilemap, int print);

#endif
