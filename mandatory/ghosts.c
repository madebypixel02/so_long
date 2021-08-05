/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghosts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:59:34 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/05 11:59:33 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	*ft_chooseghcolor(t_game *g, int i, int dir)
{
	void	*sprite;
	char	*s;

	if (dir == N)
		s = ft_substr("sprites/Ghosts/R/ghost_up.xpm", 0, 29);
	else if (dir == S)
		s = ft_substr("sprites/Ghosts/R/ghost_down.xpm", 0, 31);
	else if (dir == E)
		s = ft_substr("sprites/Ghosts/R/ghost_right.xpm", 0, 32);
	else if (dir == W)
		s = ft_substr("sprites/Ghosts/R/ghost_left.xpm", 0, 31);
	if (i > 0)
		ft_memset(&s[15], COLORS[i % 6], 1);
	sprite = mlx_xpm_file_to_image(g->id, s, &dir, &dir);
	free(s);
	return (sprite);
}

void	ft_load_ghosts(t_game *g)
{
	t_player	*temp;
	int			i;

	i = 0;
	temp = g->gh;
	while (temp)
	{
		temp->sprites.up = ft_chooseghcolor(g, i, N);
		temp->sprites.down = ft_chooseghcolor(g, i, S);
		temp->sprites.right = ft_chooseghcolor(g, i, E);
		temp->sprites.left = ft_chooseghcolor(g, i, W);
		temp = temp->next;
		i++;
	}
}

void	ft_put_ghosts(t_game *g)
{
	t_player	*ghost;

	ghost = g->gh;
	while (ghost)
	{
		mlx_put_image_to_window(g->id, g->w_id, ghost->sprites.right, \
				ghost->pos.x * SIZE, ghost->pos.y * SIZE);
		ghost = ghost->next;
	}
}
