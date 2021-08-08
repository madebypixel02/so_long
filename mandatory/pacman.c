/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 18:03:12 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/08 23:37:05 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>

void	ft_load_pacmans(t_game *g)
{
	t_player	*pacman;
	int			i;

	pacman = g->pl;
	while (pacman)
	{
		pacman->sprites.up = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_up.xpm", &i, &i);
		pacman->sprites.down = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_down.xpm", &i, &i);
		pacman->sprites.left = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_left.xpm", &i, &i);
		pacman->sprites.right = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/pac_semi_right.xpm", &i, &i);
		pacman->sprites.black = mlx_xpm_file_to_image(g->id, \
				"sprites/Pac-Man/black.xpm", &i, &i);
		pacman = pacman->next;
	}
}

void	ft_put_pacman(t_game *g)
{
	t_player	*pacman;

	pacman = g->pl;
	while (pacman)
	{
		if (pacman->dir == N)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.up, \
				pacman->win_pos.x, pacman->win_pos.y);
		if (pacman->dir == S)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.down, \
				pacman->win_pos.x, pacman->win_pos.y);
		if (pacman->dir == E || pacman->dir == ST)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.right, \
				pacman->win_pos.x, pacman->win_pos.y);
		if (pacman->dir == W)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.left, \
				pacman->win_pos.x, pacman->win_pos.y);
		pacman = pacman->next;
	}
}

void	ft_next_dir(t_game *g)
{
	t_player	*pac;
	int			n_pl;

	pac = g->pl;
	n_pl = g->lay->n_pl;
	while (pac)
	{
		if (!pac->moving)
		{
			ft_update_legal(g, pac);
			if (g->next_dir && ft_in_legal(pac, g->next_dir))
				pac->dir = g->next_dir;
			ft_move(pac->dir, g, pac);
			if (n_pl != g->lay->n_pl)
				break ;
		}
		pac = pac->next;
	}
}
