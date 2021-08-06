/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:59:34 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/06 09:43:06 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	*ft_chooseghcolor(t_game *g, int i, int dir)
{
	void	*sprite;
	char	*s;

	s = NULL;
	if (dir == N)
		s = ft_substr("sprites/Ghosts/R/ghost_up.xpm", 0, 29);
	else if (dir == S)
		s = ft_substr("sprites/Ghosts/R/ghost_down.xpm", 0, 31);
	else if (dir == E)
		s = ft_substr("sprites/Ghosts/R/ghost_right.xpm", 0, 32);
	else if (dir == W)
		s = ft_substr("sprites/Ghosts/R/ghost_left.xpm", 0, 31);
	if (i > 0)
		ft_memset(&s[15], COLORS[i % 7], 1);
	sprite = mlx_xpm_file_to_image(g->id, s, &dir, &dir);
	free(s);
	return (sprite);
}

void	ft_load_ghosts(t_game *g)
{
	t_player	*ghost;
	int			i;

	i = 0;
	ghost = g->gh;
	while (ghost)
	{
		ghost->sprites.up = ft_chooseghcolor(g, i, N);
		ghost->sprites.down = ft_chooseghcolor(g, i, S);
		ghost->sprites.right = ft_chooseghcolor(g, i, E);
		ghost->sprites.left = ft_chooseghcolor(g, i, W);
		ghost = ghost->next;
		i++;
	}
}

void	ft_put_ghosts(t_game *g)
{
	t_player	*ghost;

	ghost = g->gh;
	while (ghost)
	{
		if (ghost->dir == N)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.up, \
				ghost->pos.x * SIZE, ghost->pos.y * SIZE);
		if (ghost->dir == S)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.down, \
				ghost->pos.x * SIZE, ghost->pos.y * SIZE);
		if (ghost->dir == E || ghost->dir == ST)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.right, \
				ghost->pos.x * SIZE, ghost->pos.y * SIZE);
		if (ghost->dir == W)
			mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.left, \
				ghost->pos.x * SIZE, ghost->pos.y * SIZE);
		ghost = ghost->next;
	}
}

t_player	*ft_getnearestpac(t_game *g, t_player *ghost)
{
	int 		mindistance;
	int			distance;
	t_player	*pacman;
	t_player	*closest;

	pacman = g->pl;
	closest = NULL;
	mindistance = 0;
	while (pacman)
	{
		distance = ft_euclideandistance(ft_newvector(ghost->pos.x, ghost->pos.y), \
						ft_newvector(pacman->pos.x, pacman->pos.y));
		if (!mindistance || distance < mindistance)
		{
			closest = pacman;
			mindistance = distance;
		}
		pacman = pacman->next;
	}
	return (closest);
}
