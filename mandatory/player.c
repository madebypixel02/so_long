/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/04 11:21:34 by aperez-b         ###   ########.fr       */
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

int	ft_delete_player(t_vector old, t_player **pl)
{
	t_player	*temp;
	t_player	*prev;

	temp = *pl;
	prev = NULL;
	while (temp)
	{
		if (temp->pos.x == old.x && temp->pos.y == old.y)
		{
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
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	return (1);
}
