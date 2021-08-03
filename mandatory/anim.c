/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 10:16:09 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 11:41:18 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

/*void	ft_anim_pacdeath(t_game *g)
{

}*/

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
	t_anim	**temp;
	char	*s;
	char	c;
	int		size;

	temp = &pacdeath;
	s = ft_substr("sprites/Pac-Man/Dying/pacman_dying1.xpm", 0, 39);
	c = '0';
	while (c++ < '9' + 1)
	{
		pacdeath = ft_newanim(mlx_xpm_file_to_image(g->id, ft_memset(&s[35], c, 1), &size, &size));
		pacdeath = pacdeath->next;
	}
	pacdeath = ft_newanim(mlx_xpm_file_to_image(g->id, "sprites/Pac-Man/Dying/pacman_woosh.xpm", &size, &size));
	free(s);
	return (*temp);
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
