/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:31 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 20:52:05 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H

# define PLAYER_H

#include "vector.h"

typedef struct s_player
{
	int			is_main_player;
	t_vector	position;
	t_direction	direction;
	int			score;
	int			nLives;
	int			nMoves;
}				t_player;

#endif
