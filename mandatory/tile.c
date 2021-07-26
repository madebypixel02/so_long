/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:34:55 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 11:22:02 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/tile.h"

void	ft_newtile(t_tile *tile, int x, int y, char content)
{
	tile->posx = x;
	tile->posy = y;
	tile->content = content;
}
