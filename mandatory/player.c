/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 20:58:12 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/player.h"

void ft_newplayer(t_player *player, int x, int y, int is_main_player)
{
	player->position.x = x;
	player->position.y = y;
	player->is_main_player = is_main_player;
	player->score = 0;
	player ->nLives = 1;
	player->nMoves = 0;
}
