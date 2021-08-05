/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/05 20:40:42 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

t_player	*ft_plrnew(int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = ft_newvector(x, y);
	player->dir = ST;
	player->dying = 0;
	player->moving = 0;
	player->next = NULL;
	return (player);
}

void	ft_plradd_back(t_player **lst, t_player *newnode)
{
	t_player	*start;

	start = *lst;
	if (*lst)
	{
		while (start->next)
			start = start->next;
		start->next = newnode;
	}
	else
		*lst = newnode;
}

int	ft_delete_player(t_game *g, t_vector old, t_player **pl)
{
	t_player	*temp;
	t_player	*prev;

	temp = *pl;
	prev = NULL;
	while (temp)
	{
		if (temp->pos.x == old.x && temp->pos.y == old.y)
		{
			ft_free_singlepl(g, temp);
			temp->dying = 1;
			if (!prev)
				return (ft_deletefirst_plr(pl));
			if (prev && !temp->next)
				return (ft_deletelast_plr(pl));
			prev->next = temp->next;
			free(temp);
			temp = NULL;
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (1);
}

void	ft_checkmvtogh(t_game *g, int d, t_player *pl)
{
	if (d == N && g->map[pl->pos.y - 1][pl->pos.x] == 'G')
		g->pac_dying = 1;
	else if (d == S && g->map[pl->pos.y + 1][pl->pos.x] == 'G')
		g->pac_dying = 1;
	else if (d == E && g->map[pl->pos.y][pl->pos.x + 1] == 'G')
		g->pac_dying = 1;
	else if (d == W && g->map[pl->pos.y][pl->pos.x - 1] == 'G')
		g->pac_dying = 1;
}
