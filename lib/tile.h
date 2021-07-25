/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:32:49 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/25 19:38:56 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILE_H

# define TILE_H

# include "so_long.h"

typedef struct s_tile
{
	int		posx;
	int		posy;
	char	content;
}				t_tile;

void	ft_newtile(t_tile *tile, int x, int y, char content);

#endif
