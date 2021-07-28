/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:31 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 12:59:26 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H

# define PLAYER_H

# include "vector.h"

typedef struct s_player
{
	int			is_main_player;
	t_direction	direction;
	int			score;
	int			nLives;
	int			nMoves;
}				t_player;

t_player	ft_newplayer(int is_main_player);

#endif
