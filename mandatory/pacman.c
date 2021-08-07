/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 18:03:12 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/07 23:39:51 by aperez-b         ###   ########.fr       */
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
		pacman = pacman->next;
	}
}

void	ft_put_pacman(t_game *g)
{
	t_player	*pacman;

	pacman = g->pl;
	while (pacman)
	{
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
						pacman->pos.x * SIZE, pacman->pos.y * SIZE);
		if (pacman->dir == N)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.up, \
				pacman->pos.x * SIZE, pacman->pos.y * SIZE);
		if (pacman->dir == S)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.down, \
				pacman->pos.x * SIZE, pacman->pos.y * SIZE);
		if (pacman->dir == E || pacman->dir == ST)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.right, \
				pacman->pos.x * SIZE, pacman->pos.y * SIZE);
		if (pacman->dir == W)
			mlx_put_image_to_window(g->id, g->w_id, pacman->sprites.left, \
				pacman->pos.x * SIZE, pacman->pos.y * SIZE);
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
		ft_update_legal(g, pac);
		if (g->next_dir && ft_in_legal(pac, g->next_dir))
			pac->dir = g->next_dir;
		ft_move(pac->dir, g, pac);
		if (n_pl != g->lay->n_pl)
			break ;
		pac = pac->next;
	}
}
