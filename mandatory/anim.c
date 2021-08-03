/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 10:16:09 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 14:49:56 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	ft_anim_pacdeath(t_game *g)
{
	int	i;

	i = 0;
	if (g->sprites.pac_dying)
	{
		g->pac_dying = 1;
		while (g->p[i].pos.x != -1)
		{
			if (g->p[i].is_main_player)
			{
					mlx_put_image_to_window(g->id, g->window_id, g->sprites.black,
					g->p[i].pos.x * SPRITE_SIZE, g->p[i].pos.y * SPRITE_SIZE + OFFSET);
					mlx_put_image_to_window(g->id, g->window_id, g->sprites.pac_dying->img_ptr,
					g->p[i].pos.x * SPRITE_SIZE, g->p[i].pos.y * SPRITE_SIZE + OFFSET);
			}
			i++;
		}
		g->sprites.pac_dying = g->sprites.pac_dying->next;
	}
	else
		g->pac_dying = 0;
}

t_anim	*ft_newanim(void *img_ptr)
{
	t_anim	*anim;
	anim = malloc(sizeof(t_anim));
	if (!anim)
		return (NULL);
	anim->img_ptr = img_ptr;
	anim->next = NULL;
	return (anim);
}

t_anim	*ft_load_pacdeath(t_game *g)
{
	t_anim	*pacdeath;
	char	*s;
	char	c;
	int		size;

	pacdeath = NULL;
	s = ft_substr("sprites/Pac-Man/Dying/pacman_dying1.xpm", 0, 39);
	c = '0';
	while (c++ < '8' + 1)
	{
		ft_memset(&s[34], c, 1);
		ft_animadd_back(&pacdeath, ft_newanim(mlx_xpm_file_to_image(g->id, s, &size, &size)));
	}
	free(s);
	ft_animadd_back(&pacdeath, ft_newanim(mlx_xpm_file_to_image(g->id, "sprites/Pac-Man/Dying/pacman_dying10.xpm", &size, &size)));
	ft_animadd_back(&pacdeath, ft_newanim(mlx_xpm_file_to_image(g->id, "sprites/Pac-Man/Dying/pacman_woosh.xpm", &size, &size)));
	return (pacdeath);
}

void	free_animation(t_game *g)
{
	t_anim	*start;
	t_anim	*temp;

	start = g->sprites.pac_dying;
	temp = NULL;
	while (start)
	{
		temp = start;
		start = start->next;
		mlx_destroy_image(g->id, temp->img_ptr);
		free(temp);
	}
}

void		ft_animadd_back(t_anim **anim, t_anim  *newnode)
{
	t_anim	*start;

	if (*anim)
	{
		start = *anim;
		while (start->next)
			start = start->next;
		start->next = newnode;
	}
	else
		*anim = newnode;
}
