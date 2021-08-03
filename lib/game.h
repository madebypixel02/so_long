/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 17:24:04 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "colors.h"
# include "../libft/lib/libft.h"
# include "../mlx.h"
# include <stdio.h>

# define SIZE 32
# define OFFSET 60

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

typedef struct s_anim
{
	void			*img_ptr;
	struct s_anim	*next;
}				t_anim;

typedef struct s_sprite
{
	void		*pacman;
	void		*ghost;
	void		*logo;
	void		**wall;
	void		*pacfood;
	void		*portal;
	void		*black;
	t_anim		*pac_dying;
	t_anim		*pac_moving;
}				t_sprite;

typedef struct s_player
{
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
	int			pac_dying;
	int			pac_moving;
	int			g_rate;
	int			anim_rate;
	void		*id;
	void		*w_id;
	int			n_frames;
	int			n_moves;
	int			redraw;
	t_player	*p;
}				t_game;

void		init_game(char **map, t_lay *lay);
t_game		ft_newgame(char **map, t_lay *lay);
int			end_game(t_game *g);
int			ft_update(t_game *g);
int			key_hook(int keycode, t_game *g);
t_sprite	ft_initsprites(t_game *g);
int			free_sprites(t_game *g);
void		ft_check_game(t_game *g);
void		ft_newdirection(t_game *g, int direction);
t_player	ft_newplayer(int x, int y);
t_player	*ft_playerlist(char **map, t_game *g);
void		move(char ***m, int d, t_game *g);
int			ft_swap_tile(char ***m, t_vector old, t_vector nw, t_game *g);
t_vector	ft_newvector(int x, int y);
void		ft_redraw(t_vector old, t_vector nw, t_game *g, int hide);
void		ft_put_map(t_game *g, int x, int y);
void		ft_anim_pacdeath(t_game *g);
t_anim		*ft_load_pacdeath(t_game *g);
t_anim		*ft_newanim(void *img_ptr);
void		ft_put_extras(t_game *g);
void		ft_animadd_back(t_anim **anim, t_anim *newnode);
void		free_animation(t_game *g);

#endif
