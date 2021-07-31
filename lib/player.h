/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:35:31 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 10:27:07 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H

# define PLAYER_H

# include "map.h"
# include "../libft/lib/libft.h"

enum e_direction
{
	STOP = 0,
	NORTH = 1,
	SOUTH = -1,
	EAST = 2,
	WEST = -2
};

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_player
{
	int			is_main_player;
	t_vector	pos;
	t_lay		*lay;
	int			dir;
	int			score;
	int			n_lives;
	int			n_moves;
}				t_player;

t_player	ft_newplayer(int is_main_player, int x, int y, t_lay *lay);
t_player	*ft_playerlist(char **map, t_lay *lay);
int			move(char ***map, int d, t_player *p);
int			ft_swap_tile(char ***m, t_vector old, t_vector nw, t_player *p);
t_vector	ft_newvector(int x, int y);

#endif
