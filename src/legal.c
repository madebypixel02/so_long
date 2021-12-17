/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 10:43:50 by aperez-b          #+#    #+#             */
/*   Updated: 2021/12/17 14:20:49 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	ft_update_legal(t_game *g, t_player *gh)
{
	gh->legal.north = (!ft_strchr("1G", g->map[gh->pos.y - 1][gh->pos.x]) \
		&& !ft_findghost(g->gh, ft_newvector(gh->pos.x, gh->pos.y - 1)));
	gh->legal.south = (!ft_strchr("1G", g->map[gh->pos.y + 1][gh->pos.x]) \
		&& !ft_findghost(g->gh, ft_newvector(gh->pos.x, gh->pos.y + 1)));
	gh->legal.east = (!ft_strchr("1G", g->map[gh->pos.y][gh->pos.x + 1]) \
		&& !ft_findghost(g->gh, ft_newvector(gh->pos.x + 1, gh->pos.y)));
	gh->legal.west = (!ft_strchr("1G", g->map[gh->pos.y][gh->pos.x - 1]) \
		&& !ft_findghost(g->gh, ft_newvector(gh->pos.x - 1, gh->pos.y)));
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

int	ft_in_legal(t_player *player, int dir)
{
	if (dir == N && player->legal.north)
		return (1);
	if (dir == S && player->legal.south)
		return (1);
	if (dir == E && player->legal.east)
		return (1);
	if (dir == W && player->legal.west)
		return (1);
	if (dir == ST)
		return (1);
	return (0);
}
