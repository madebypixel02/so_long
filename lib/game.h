/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 09:28:01 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "colors.h"
# include "../libft/lib/libft.h"
# include "../mlx.h"
# include <stdio.h>

# define SPRITE_SIZE 32
# define OFFSET 60
# define GAMERATE 10000

enum e_direction
{
	ST = 0,
	N = 1,
	S = -1,
	E = 2,
	W = -2
};

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_sprite
{
	void		*pacman;
	void		*logo;
	void		**wall;
	void		*pacfood;
	void		*portal;
	void		*black;
}				t_sprite;

typedef struct s_player
{
	int			is_main_player;
	t_vector	pos;
	int			dir;
}				t_player;

typedef struct s_game
{
	int			width;
	int			height;
	t_lay		*lay;
	char		**map;
	t_sprite	sprites;
	void		*id;
	void		*window_id;
	int			n_frames;
	int			n_moves;
	int			redraw;
	t_player	*p;
}				t_game;

void		init_game(char **map, t_lay *lay);
t_game		ft_newgame(char **map, t_lay *lay);
int			end_game(t_game *game);
int			ft_update(t_game *game);
int			key_hook(int keycode, t_game *game);
t_sprite	ft_initsprites(t_game *game);
int			free_sprites(t_game *game, int only_pac);
void		ft_newdirection(t_game *game, int direction);
t_player	ft_newplayer(int is_main_player, int x, int y);
t_player	*ft_playerlist(char **map, t_game *g);
void		move(char ***map, int d, t_game *g);
int			ft_swap_tile(char ***m, t_vector old, t_vector nw, t_game *g);
t_vector	ft_newvector(int x, int y);
void		ft_redraw(t_vector old, t_vector nw, t_game *g, int hide);
void		ft_print_static(t_game *g, int x, int y);

#endif
