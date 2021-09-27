/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 11:04:12 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 20:00:57 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <mlx.h>
#include <unistd.h>

void	ft_load_pacmans(t_game *g)
{
	t_player	*pacman;
	int			i;

	i = 0;
	pacman = g->pl;
	while (pacman)
	{
		pacman->sprites.up = ft_load_north(g, NULL, i);
		pacman->sprites.up_bak = pacman->sprites.up;
		pacman->sprites.down = ft_load_south(g, NULL, i);
		pacman->sprites.down_bak = pacman->sprites.down;
		pacman->sprites.left = ft_load_west(g, NULL, i);
		pacman->sprites.left_bak = pacman->sprites.left;
		pacman->sprites.right = ft_load_east(g, NULL, i);
		pacman->sprites.right_bak = pacman->sprites.right;
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
			pacman->win_pos.x, pacman->win_pos.y);
		if (pacman->dir == N && pacman->moving)
			ft_anim_north(g, pacman);
		if (pacman->dir == S && pacman->moving)
			ft_anim_south(g, pacman);
		if (pacman->dir == E && pacman->moving)
			ft_anim_east(g, pacman);
		if (pacman->dir == W && pacman->moving)
			ft_anim_west(g, pacman);
		if (pacman->dir == ST)
			mlx_put_image_to_window(g->id, g->w_id, g->sprites.pacman, \
				pacman->win_pos.x, pacman->win_pos.y);
		else if (!pacman->moving)
			ft_put_stopped(g, pacman);
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
