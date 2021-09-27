/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 11:05:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 20:03:36 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	ft_anim_north(t_game *g, t_player *pl)
{
	t_player	*temp;

	temp = pl;
	if (!(g->n_frames % (((g->panic_mode * 7 + g->g_rate) + g->g_rate) / 7)))
		temp->sprites.up = temp->sprites.up->next;
	if (!temp->sprites.up)
		temp->sprites.up = temp->sprites.up_bak;
	mlx_put_image_to_window(g->id, g->w_id, temp->sprites.up->content, \
		temp->win_pos.x, temp->win_pos.y);
}

void	ft_anim_south(t_game *g, t_player *pl)
{
	t_player	*temp;

	temp = pl;
	if (!(g->n_frames % (((g->panic_mode * 7 + g->g_rate) + g->g_rate) / 7)))
		temp->sprites.down = temp->sprites.down->next;
	if (!temp->sprites.down)
		temp->sprites.down = temp->sprites.down_bak;
	mlx_put_image_to_window(g->id, g->w_id, temp->sprites.down->content, \
		temp->win_pos.x, temp->win_pos.y);
}

void	ft_anim_east(t_game *g, t_player *pl)
{
	t_player	*temp;

	temp = pl;
	if (!(g->n_frames % (((g->panic_mode * 7 + g->g_rate) + g->g_rate) / 7)))
		temp->sprites.right = temp->sprites.right->next;
	if (!temp->sprites.right)
		temp->sprites.right = temp->sprites.right_bak;
	mlx_put_image_to_window(g->id, g->w_id, temp->sprites.right->content, \
		temp->win_pos.x, temp->win_pos.y);
}

void	ft_anim_west(t_game *g, t_player *pl)
{
	t_player	*temp;

	temp = pl;
	if (!(g->n_frames % (((g->panic_mode * 7 + g->g_rate) + g->g_rate) / 7)))
		temp->sprites.left = temp->sprites.left->next;
	if (!temp->sprites.left)
		temp->sprites.left = temp->sprites.left_bak;
	mlx_put_image_to_window(g->id, g->w_id, temp->sprites.left->content, \
		temp->win_pos.x, temp->win_pos.y);
}

void	ft_anim_panic(t_game *g, t_player *pl)
{
	t_player	*temp;

	temp = pl;
	if (!(g->n_frames % (g->g_rate / 3)))
		temp->sprites.panic = temp->sprites.panic->next;
	if (!temp->sprites.panic)
		temp->sprites.panic = temp->sprites.panic_bak;
	mlx_put_image_to_window(g->id, g->w_id, temp->sprites.panic->content, \
		temp->win_pos.x, temp->win_pos.y);
}
