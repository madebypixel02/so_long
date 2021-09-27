/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 10:23:45 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 19:59:54 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

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

int	ft_choose_dir(t_game *g, t_player *gh, t_player *pac)
{
	int		len;
	int		*distances;

	ft_update_legal(g, gh);
	ft_restrict_legal(gh);
	len = ft_legal_len(gh);
	if (len > 1)
	{
		distances = malloc(5 * sizeof(int));
		if (!distances)
		{
			printf("%sMemory Allocation Error!%s\n", RED, DEFAULT);
			return (end_game(g));
		}
		return (ft_advanced_dir(gh, pac, distances));
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

int	ft_advanced_dir(t_player *gh, t_player *pac, int *distances)
{
	int	i;

	i = 0;
	if (gh->legal.north)
		distances[i++] = ft_euclideandistance(ft_newvector(gh->pos.x, \
			gh->pos.y - 1), ft_newvector(pac->pos.x, pac->pos.y));
	else
		distances[i++] = -2;
	if (gh->legal.south)
		distances[i++] = ft_euclideandistance(ft_newvector(gh->pos.x, \
			gh->pos.y + 1), ft_newvector(pac->pos.x, pac->pos.y));
	else
		distances[i++] = -2;
	if (gh->legal.east)
		distances[i++] = ft_euclideandistance(ft_newvector(gh->pos.x + 1, \
			gh->pos.y), ft_newvector(pac->pos.x, pac->pos.y));
	else
		distances[i++] = -2;
	if (gh->legal.west)
		distances[i++] = ft_euclideandistance(ft_newvector(gh->pos.x - 1, \
			gh->pos.y), ft_newvector(pac->pos.x, pac->pos.y));
	else
		distances[i++] = -2;
	distances[i] = -1;
	return (ft_advanced_dir2(distances));
}

int	ft_advanced_dir2(int *distances)
{
	int	min;
	int	i;
	int	j;

	i = -1;
	j = 0;
	min = -1;
	while (distances[++i] != -1)
	{
		if (distances[i] >= 0 && (min == -1 || distances[i] < min))
		{
			min = distances[i];
			j = i;
		}
	}
	free(distances);
	if (j == 0)
		return (N);
	if (j == 1)
		return (S);
	if (j == 2)
		return (E);
	if (j == 3)
		return (W);
	return (ST);
}

int	ft_findghost(t_player *pl, t_vector pos)
{
	t_player	*gh;

	gh = pl;
	while (gh)
	{
		if (gh->pos.x == pos.x && gh->pos.y == pos.y)
			return (1);
		gh = gh->next;
	}
	return (0);
}
