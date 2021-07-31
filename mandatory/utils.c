/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 17:13:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 17:21:16 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	ft_newdirection(t_game *game, int direction)
{
	int	i;

	i = 0;
	printf("%d\n", game->n_moves++);
	while (game->p[i].pos.x != -1 && game->p[i].pos.y != -1)
	{
		if (game->p[i].is_main_player)
			game->p[i].dir = direction;
		i++;
	}
}