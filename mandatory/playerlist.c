/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:33:55 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/04 11:05:13 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

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

int	ft_deletefirst_plr(t_player **pl)
{
	t_player	*head;

	head = *pl;
	if (head->next)
		*pl = head->next;
	else
		*pl = NULL;
	free(head);
	head = NULL;
	return (1);
}

int	ft_deletelast_plr(t_player **pl)
{
	t_player	*head;

	head = *pl;
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
				ft_plradd_back(&g->pl, ft_plrnew(x, y));
			if (map[y][x] == 'G')
				ft_plradd_back(&g->gh, ft_plrnew(x, y));
			x++;
		}
		y++;
	}
}
