/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 20:07:55 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

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

t_player	*ft_plrnew(int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = ft_newvector(x, y);
	player->dir = ST;
	player->next = NULL;
	return (player);
}

void	ft_redraw(t_vector old, t_vector nw, t_game *g, int hide)
{
	int	size;

	mlx_destroy_image(g->id, g->sprites.pacman);
	if (g->pl && g->pl->dir == N)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_up.xpm", &size, &size);
	if (g->pl && g->pl->dir == S)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_down.xpm", &size, &size);
	if (g->pl && g->pl->dir == E)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_right.xpm", &size, &size);
	if (g->pl && g->pl->dir == W)
		g->sprites.pacman = mlx_xpm_file_to_image(g->id, \
			"sprites/Pac-Man/pac_semi_left.xpm", &size, &size);
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
		old.x * SIZE, old.y * SIZE + OFFSET);
	mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
		nw.x * SIZE, nw.y * SIZE + OFFSET);
	if (!hide)
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacman, \
			nw.x * SIZE, nw.y * SIZE + OFFSET);
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
