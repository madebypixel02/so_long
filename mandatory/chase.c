/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 10:23:45 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/06 12:36:37 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

t_player	*ft_getnearestpac(t_game *g, t_player *ghost)
{
	int			mindistance;
	int			distance;
	t_player	*pacman;
	t_player	*closest;

	pacman = g->pl;
	closest = NULL;
	mindistance = 0;
	while (pacman)
	{
		distance = ft_euclideandistance(ft_newvector(ghost->pos.x, \
				ghost->pos.y), ft_newvector(pacman->pos.x, pacman->pos.y));
		if (!mindistance || distance < mindistance)
		{
			closest = pacman;
			mindistance = distance;
		}
		pacman = pacman->next;
	}
	return (closest);
}

int	ft_choose_dir(t_player *gh, t_player *pac)
{
	int	len;

	ft_restrict_legal(gh);
	len = ft_legal_len(gh);
	if (len > 1)
	{
		if (gh->pos.y > pac->pos.y && gh->legal.north)
			return (N);
		if (gh->pos.y < pac->pos.y && gh->legal.south)
			return (S);
		if (gh->pos.x < pac->pos.x && gh->legal.east)
			return (E);
		if (gh->pos.x > pac->pos.x && gh->legal.west)
			return (W);
	}
	if (gh->legal.north)
		return (N);
	if (gh->legal.south)
		return (S);
	if (gh->legal.east)
		return (E);
	if (gh->legal.west)
		return (W);
	return (ST);
}
