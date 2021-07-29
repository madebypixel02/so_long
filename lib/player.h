/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:31 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/29 22:34:27 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H

# define PLAYER_H

enum e_direction
{
	STOP = 0,
	NORTH = 1,
	SOUTH = -1,
	EAST = 2,
	WEST = -2
};

typedef struct s_player
{
	int		is_main_player;
	int		direction;
	int		score;
	int		nLives;
	int		nMoves;
}				t_player;

t_player	ft_newplayer(int is_main_player);

#endif
