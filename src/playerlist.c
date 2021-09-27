/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:33:55 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 20:01:58 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	ft_free_playerlist(t_game *g)
{
	t_player	*temp;

	while (g->pl)
	{
		temp = g->pl;
		g->pl = g->pl->next;
		free(temp);
		temp = NULL;
	}
	while (g->gh)
	{
		temp = g->gh;
		g->gh = g->gh->next;
		free(temp);
		temp = NULL;
	}
}

int	ft_deletefirst_plr(t_game *g)
{
	t_player	*head;

	head = g->pl;
	if (head->next)
		g->pl = head->next;
	else
		g->pl = NULL;
	free(head);
	head = NULL;
	return (1);
}

int	ft_deletelast_plr(t_game *g)
{
	t_player	*head;

	head = g->pl;
	while (head->next->next)
		head = head->next;
	free(head->next);
	head->next = NULL;
	return (1);
}

void	ft_playerlist(char **map, t_game *g)
{
	int			x;
	int			y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				ft_plradd_back(&g->pl, ft_plrnew(ft_newvector(x, y)));
			if (map[y][x] == 'G')
				ft_plradd_back(&g->gh, ft_plrnew(ft_newvector(x, y)));
			x++;
		}
		y++;
	}
}
