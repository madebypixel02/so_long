/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/29 23:22:37 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "colors.h"

# define SPRITE_SIZE 64

enum e_keycodes
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_R = 114,
	KEY_Q = 113,
};

typedef struct s_game
{
	int		width;
	int		height;
	char	**map;
	void	*id;
	void	*window_id;
	int		nFrames;
}				t_game;

void	init_game(char **map, t_lay *lay);
t_game	ft_newgame(char **map, t_lay lay);
void	free_gamemap(t_game *game, int print);
int		end_game(t_game *game);
int		print_map(t_game *game);

#endif
