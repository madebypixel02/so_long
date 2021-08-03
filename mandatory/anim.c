/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 10:16:09 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 20:08:36 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	ft_anim_pacdeath(t_game *g)
{
	t_player	*temp_pl;

	temp_pl = g->pl;
	if (g->sprites.pac_dying)
	{
		g->pac_dying = 1;
		while (temp_pl)
		{
			mlx_put_image_to_window(g->id, g->w_id, g->sprites.black, \
				temp_pl->pos.x * SIZE, temp_pl->pos.y * SIZE + OFFSET);
			mlx_put_image_to_window(g->id, g->w_id,
				g->sprites.pac_dying->content, temp_pl->pos.x * SIZE, \
			temp_pl->pos.y * SIZE + OFFSET);
			temp_pl = temp_pl->next;
		}
		g->sprites.pac_dying = g->sprites.pac_dying->next;
	}
	else
		g->pac_dying = 0;
}

t_list	*ft_load_pacdeath(t_game *g)
{
	t_list	*pacdeath;
	char	*s;
	char	c;
	int		size;

	pacdeath = NULL;
	s = ft_substr("sprites/Pac-Man/Dying/pacman_dying1.xpm", 0, 39);
	c = '0';
	while (c++ < '8' + 1)
	{
		ft_memset(&s[34], c, 1);
		ft_lstadd_back(&pacdeath, \
			ft_lstnew(mlx_xpm_file_to_image(g->id, s, &size, &size)));
	}
	free(s);
	ft_lstadd_back(&pacdeath, ft_lstnew(mlx_xpm_file_to_image(g->id, \
		"sprites/Pac-Man/Dying/pacman_dying10.xpm", &size, &size)));
	ft_lstadd_back(&pacdeath, ft_lstnew(mlx_xpm_file_to_image(g->id, \
		"sprites/Pac-Man/Dying/pacman_woosh.xpm", &size, &size)));
	return (pacdeath);
}

void	free_animation(t_game *g)
{
	t_list		*start;
	t_list		*temp;

	start = g->sprites.pac_dying_bak;
	temp = NULL;
	while (start)
	{
		temp = start;
		start = start->next;
		mlx_destroy_image(g->id, temp->content);
		free(temp);
	}
}
