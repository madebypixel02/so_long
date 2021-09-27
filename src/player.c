/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 20:03:02 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <mlx.h>
#include <stdio.h>

t_player	*ft_plrnew(t_vector pos)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = pos;
	player->win_pos = ft_newvector(pos.x * SIZE, pos.y * SIZE);
	player->moving = 0;
	player->dir = ST;
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

int	ft_delete_player(t_game *g, t_vector old)
{
	t_player	*temp;
	t_player	*prev;

	temp = g->pl;
	prev = NULL;
	g->lay->n_pl--;
	while (temp)
	{
		if (temp->pos.x == old.x && temp->pos.y == old.y)
		{
			ft_free_singlepl(g, temp);
			if (!prev)
				return (ft_deletefirst_plr(g));
			if (prev && !temp->next)
				return (ft_deletelast_plr(g));
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

int	ft_checkmvtogh(t_game *g, int d, t_player *pl)
{
	t_player	*gh;

	gh = g->gh;
	while (gh)
	{
		if (d == N && pl->pos.y - 1 == gh->pos.y && pl->pos.x == gh->pos.x)
			g->pac_dying = 1;
		if (d == S && pl->pos.y + 1 == gh->pos.y && pl->pos.x == gh->pos.x)
			g->pac_dying = 1;
		if (d == E && pl->pos.y == gh->pos.y && pl->pos.x + 1 == gh->pos.x)
			g->pac_dying = 1;
		if (d == W && pl->pos.y == gh->pos.y && pl->pos.x - 1 == gh->pos.x)
			g->pac_dying = 1;
		if (pl->pos.y == gh->pos.y && pl->pos.x == gh->pos.x)
			g->pac_dying = 1;
		gh = gh->next;
	}
	return (g->pac_dying);
}

int	ft_update(t_game *g)
{
	int		x;
	int		y;

	y = 0;
	g->n_frames++;
	ft_check_game(g);
	if (g->redraw)
	{
		ft_put_ghosts(g);
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.logo, \
		(g->width - 131) / 2, g->height - 42);
		ft_update_score(g);
		while (g->map[y])
		{
			x = 0;
			while (g->map[y][x])
			{
				ft_put_map(g, x, y);
				x++;
			}
			y++;
		}
		g->redraw = 0;
	}
	return (0);
}
