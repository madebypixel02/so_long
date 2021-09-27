/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:13:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 20:00:24 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <mlx.h>
#include <unistd.h>

void	ft_newdirection(t_game *g, int direction)
{
	t_player	*temp;

	temp = g->pl;
	if (g->n_moves < 9999)
	{
		g->n_moves++;
		ft_update_score(g);
	}
	while (temp)
	{
		g->next_dir = direction;
		temp = temp->next;
	}
}

void	ft_move(int d, t_game *g, t_player *temp)
{
	t_vector	nw;

	if (temp && !ft_checkmvtogh(g, d, temp))
	{
		if (d == N && ft_strchr("0CE", g->map[temp->pos.y - 1][temp->pos.x]))
			nw = ft_newvector(temp->pos.x, temp->pos.y - 1);
		else if (d == S && ft_strchr("0CE", \
				g->map[temp->pos.y + 1][temp->pos.x]))
			nw = ft_newvector(temp->pos.x, temp->pos.y + 1);
		else if (d == E && ft_strchr("0CE", \
				g->map[temp->pos.y][temp->pos.x + 1]))
			nw = ft_newvector(temp->pos.x + 1, temp->pos.y);
		else if (d == W && ft_strchr("0CE", \
				g->map[temp->pos.y][temp->pos.x - 1]))
			nw = ft_newvector(temp->pos.x - 1, temp->pos.y);
		else
			nw = ft_newvector(0, 0);
		if (g->map[nw.y][nw.x] == 'C')
			g->lay->n_collect--;
		if (nw.x && nw.y)
			ft_swap_tile(ft_newvector(temp->pos.x, temp->pos.y), nw, g);
	}
}

int	ft_swap_tile(t_vector old, t_vector nw, t_game *g)
{
	t_player	*player;
	int			hide;

	player = g->pl;
	hide = 0;
	if (g->map[nw.y][nw.x] == 'E')
	{
		if (g->lay->n_collect)
			return (1);
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
			old.x * SIZE, old.y * SIZE);
		hide = ft_delete_player(g, old);
	}
	while (!hide && player)
	{
		if (player->pos.x == old.x && player->pos.y == old.y)
		{
			player->pos = ft_newvector(nw.x, nw.y);
			player->moving = 1;
		}
		player = player->next;
	}
	ft_memset(&g->map[nw.y][nw.x], g->map[old.y][old.x], !hide);
	ft_memset(&g->map[old.y][old.x], '0', 1);
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
