/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:13:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/08 02:29:53 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <unistd.h>

void	ft_newdirection(t_game *g, int direction)
{
	t_player	*temp;

	temp = g->pl;
	g->n_moves++;
	ft_update_score(g);
	while (temp)
	{
		g->next_dir = direction;
		temp = temp->next;
	}
}

void	ft_move(int d, t_game *g, t_player *temp)
{
	if (temp && !ft_checkmvtogh(g, d, temp))
	{
		if (d == N && ft_strchr("0CEG", g->map[temp->pos.y - 1][temp->pos.x]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x, temp->pos.y - 1), g);
		if (d == S && ft_strchr("0CEG", g->map[temp->pos.y + 1][temp->pos.x]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x, temp->pos.y + 1), g);
		if (d == E && ft_strchr("0CEG", g->map[temp->pos.y][temp->pos.x + 1]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x + 1, temp->pos.y), g);
		if (d == W && ft_strchr("0CEG", g->map[temp->pos.y][temp->pos.x - 1]))
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), \
				ft_newvector(temp->pos.x - 1, temp->pos.y), g);
	}
}

int	ft_swap_tile(t_vector old, t_vector nw, t_game *g)
{
	t_player	*player;
	int			hide;

	player = g->pl;
	hide = 0;
	if (g->map[nw.y][nw.x] == 'C')
		g->lay->n_collect--;
	if (g->map[nw.y][nw.x] == 'E' && !g->lay->n_collect)
	{
		hide = 1;
		g->lay->n_pl--;
		ft_delete_player(g, old);
	}
	else if (g->map[nw.y][nw.x] == 'E')
		return (1);
	while (!hide && player)
	{
		if (player->pos.x == old.x && player->pos.y == old.y)
			player->pos = ft_newvector(nw.x, nw.y);
		player = player->next;
	}
	ft_memset(&g->map[nw.y][nw.x], g->map[old.y][old.x], !hide);
	ft_memset(&g->map[old.y][old.x], '0', 1);
	ft_redraw(ft_newvector(old.x, old.y), ft_newvector(nw.x, nw.y), g, hide);
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

int	ft_reset(t_game *g)
{
	t_lay	lay;
	char	**map;

	map = ft_dup_matrix(g->map_bak);
	if (!map)
		return (0);
	lay = g->lay_bak;
	if (g->map)
		ft_free_matrix(&g->map);
	free_sprites(g);
	ft_free_playerlist(g);
	mlx_clear_window(g->id, g->w_id);
	printf("\n%sGAME HAS BEEN RESET!\n%s", YELLOW, DEFAULT);
	ft_newgame(g, map, &lay);
	return (1);
}
