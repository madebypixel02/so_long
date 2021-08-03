/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 17:44:46 by aperez-b         ###   ########.fr       */
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

/* Enum for North, South, East, West as ints */
enum e_direction
{
	ST = 0,
	N = 1,
	S = -1,
	E = 2,
	W = -2
};

/* Vector with x and y coordinates */
typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

/* Linked list to handle animations */
typedef struct s_anim
{
	void			*img_ptr;
	struct s_anim	*next;
}				t_anim;

/* MLX image pointers */
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

/* Main Player struct with position and direction (linked list) */
typedef struct s_player
{
	t_vector	pos;
	int			dir;
}				t_player;

/* Main attributes for the game */
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

/* Initiates game object and starts looking for input */
void		init_game(char **map, t_lay *lay);

/* Starts game with all attributes */
t_game		ft_newgame(char **map, t_lay *lay);

/* Stops execution and frees allocated memory */
int			end_game(t_game *g);

/* Main loop that prints map and updates all events in the game */
int			ft_update(t_game *g);

/* MLX hook to move pacman on input */
int			key_hook(int keycode, t_game *g);

/* Retrieve void pointers for sprite struct */
t_sprite	ft_initsprites(t_game *g);

/* Free everything sprite-related (includes animations ) */
int			free_sprites(t_game *g);

/* Checks current state of the game to end or update it */
void		ft_check_game(t_game *g);

/* Updates all players' direction after moving */
void		ft_newdirection(t_game *g, int direction);

/* Creates new player in a given position */
t_player	ft_newplayer(int x, int y);

/* Creates array of players for future use */
t_player	*ft_playerlist(char **map, t_game *g);

/* Checks 2D map and updates player's position if possible */
void		move(char ***m, int d, t_game *g);

/* Helper tool for move function */
int			ft_swap_tile(char ***m, t_vector old, t_vector nw, t_game *g);

/* Creates new vector with given x and y */
t_vector	ft_newvector(int x, int y);

/* Re-Draws Pacmans and the floor if necessary to new position */
void		ft_redraw(t_vector old, t_vector nw, t_game *g, int hide);

/* Draws walls, collectibles, and initial positions for players/enemies */
void		ft_put_map(t_game *g, int x, int y);

/* Iterates to animate pacman's death */
void		ft_anim_pacdeath(t_game *g);

/* Loads necessary sprites (mlx) for pacman's death */
t_anim		*ft_load_pacdeath(t_game *g);

/* Creates linked list node for animation */
t_anim		*ft_newanim(void *img_ptr);

/* Draws Score, Moves, and pacman logo */
void		ft_put_extras(t_game *g);

/* lstadd_back for animations */
void		ft_animadd_back(t_anim **anim, t_anim *newnode);

/* Frees all nodes in animation list */
void		free_animation(t_game *g);

#endif
