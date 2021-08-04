/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:13:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/04 09:48:06 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	ft_newdirection(t_game *g, int direction)
{
	t_player	*temp;

	temp = g->pl;
	printf("%d\n", g->n_moves++);
	while (temp)
	{
		temp->dir = direction;
		temp = temp->next;
	}
}

t_vector	ft_newvector(int x, int y)
{
	t_vector	position;

	position.x = x;
	position.y = y;
	return (position);
}

int	move(int d, t_game *g, t_player **pl)
{
	t_player	*temp;
	char		***m;
	int			old_n_pl;

	m = &g->map;
	temp = *pl;
	old_n_pl = g->lay->n_pl;
	while (temp)
	{

		if (d == N && ft_strchr("0CE", m[0][temp->pos.y - 1][temp->pos.x]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x, temp->pos.y - 1), g, pl);
		if (d == S && ft_strchr("0CE", m[0][temp->pos.y + 1][temp->pos.x]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x, temp->pos.y + 1), g, pl);
		if (d == E && ft_strchr("0CE", m[0][temp->pos.y][temp->pos.x + 1]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x + 1, temp->pos.y), g, pl);
		if (d == W && ft_strchr("0CE", m[0][temp->pos.y][temp->pos.x - 1]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x - 1, temp->pos.y), g, pl);
		if (old_n_pl != g->lay->n_pl)
			return (1);
		temp = temp->next;
	}
	return (1);
}

int	ft_swap_tile(t_vector old, t_vector nw, t_game *g, t_player **pl)
{
	t_player	*temp;
	char		***m;

	m = &g->map;
	temp = g->pl;
	if (m[0][nw.y][nw.x] == 'C')
		g->lay->n_collect--;
	if (m[0][nw.y][nw.x] == 'E' && !g->lay->n_collect)
	{
		ft_delete_player(old, pl);
		g->lay->n_pl--;
	}
	else if (m[0][nw.y][nw.x] == 'E')
		return (1);
	else
	{
		while (temp)
		{
			if (temp->pos.x == old.x && temp->pos.y == old.y
				&& ft_strchr("C0", m[0][nw.y][nw.x]))
				temp->pos = ft_newvector(nw.x, nw.y);
			temp = temp->next;
		}
		ft_memset(&m[0][nw.y][nw.x], m[0][old.y][old.x], 1);
		ft_memset(&m[0][old.y][old.x], '0', 1);
		ft_redraw(ft_newvector(old.x, old.y), ft_newvector(nw.x, nw.y), g, 0);
	}
	return (1);
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

void	ft_print_plrs(t_game *g)
{
	t_player	*head;

	head = g->pl;
	printf("PLAYERS: ");
	while (head)
	{
		printf("(%d, %d) ", head->pos.x, head->pos.y);
		head = head->next;
	}
	head = g->gh;
	printf("\nGHOSTS:");
	while (head)
	{
		printf("(%d, %d) ", head->pos.x, head->pos.y);
		head = head->next;
	}
	printf("\n");
}
