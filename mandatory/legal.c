/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 10:43:50 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/06 11:16:29 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	ft_update_legal(t_game *g)
{
	t_player	*ghost;

	ghost = g->gh;
	while (ghost)
	{
		ghost->legal.north = g->map[ghost->pos.y - 1][ghost->pos.x] != '1';
		ghost->legal.south = g->map[ghost->pos.y + 1][ghost->pos.x] != '1';
		ghost->legal.east = g->map[ghost->pos.y][ghost->pos.x + 1] != '1';
		ghost->legal.east = g->map[ghost->pos.y][ghost->pos.x - 1] != '1';
		ghost = ghost->next;
	}
}

void	ft_restrict_legal(t_player *ghost)
{
	if (ft_legal_len(ghost) != 1)
	{
		if (ghost->dir == N)
			ghost->legal.south = 0;
		if (ghost->dir == S)
			ghost->legal.north = 0;
		if (ghost->dir == E)
			ghost->legal.west = 0;
		if (ghost->dir == W)
			ghost->legal.east = 0;
	}
}

int	ft_legal_len(t_player *player)
{
	int	count;

	count = 0;
	count += player->legal.north;
	count += player->legal.south;
	count += player->legal.east;
	count += player->legal.west;
	return (count);
}
