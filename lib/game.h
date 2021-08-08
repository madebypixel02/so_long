/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/08 17:03:46 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "colors.h"
# include "../libft/lib/libft.h"
# include <mlx.h>
# include <stdio.h>

# define SIZE 32
# define COLORS "RBGOYKP"

/* Enum for North, South, East, West as ints */
enum e_direction
{
	ST = 0,
	N = 1,
	S = -1,
	E = 2,
	W = -2
};

typedef struct s_font
{
	void	*zero;
	void	*one;
	void	*two;
	void	*three;
	void	*four;
	void	*five;
	void	*six;
	void	*seven;
	void	*eight;
	void	*nine;
	void	*black;
}				t_font;

typedef struct s_pl_sprite
{
	void	*up;
	void	*down;
	void	*left;
	void	*right;
	void	*panic1;
	void	*panic2;
	void	*black;
	char	*pixels;
}				t_pl_sprite;

/* MLX image pointers */
typedef struct s_sprite
{
	void		*logo;
	void		**wall;
	void		*pacfood;
	void		*portal;
	void		*pacman;
	void		*pixels;
	t_list		*pac_dying_bak;
	t_list		*pac_dying;
	t_font		score_font;
}				t_sprite;

/*  */
typedef struct s_legal_actions
{
	int	north;
	int	south;
	int	east;
	int	west;
}				t_legal_actions;

/* Main Player struct with position and direction (linked list) */
typedef struct s_player
{
	t_vector		pos;
	t_vector		win_pos;
	int				dir;
	int				moving;
	t_pl_sprite		sprites;
	t_legal_actions	legal;
	struct s_player	*next;
}				t_player;

/* Main attributes for the game */
typedef struct s_game
{
	int			width;
	int			height;
	t_lay		*lay;
	int			next_dir;
	t_lay		lay_bak;
	char		**map;
	int			endian;
	char		**map_bak;
	t_sprite	sprites;
	int			pac_dying;
	int			panic_mode;
	void		*id;
	void		*w_id;
	int			n_frames;
	int			n_moves;
	int			redraw;
	int			n_collect_bak;
	int			g_rate;
	t_player	*pl;
	t_player	*gh;
}				t_game;

/* Initiates game object and starts looking for input */
void		init_game(char **map, t_lay lay);

/* Starts game with all attributes */
void		ft_newgame(t_game *g, char **m, t_lay *lay);

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
t_player	*ft_plrnew(t_vector pos);

/* ft_lstadd_back for player struct */
void		ft_plradd_back(t_player **lst, t_player *newnode);

/* Creates array of players for future use */
void		ft_playerlist(char **map, t_game *g);

/* Frees linked lists for players and ghosts */
void		ft_free_playerlist(t_game *g);

/* Deletes first element of linked list of players */
int			ft_deletefirst_plr(t_game *g);

/* Deletes last player from linked list */
int			ft_deletelast_plr(t_game *g);

/* Deletes the player in a specific position from list */
int			ft_delete_player(t_game *g, t_vector old);

/* Prints current list of players and ghost */
void		ft_print_plrs(t_game *g);

/* Checks 2D map and updates player's position if possible */
void		ft_move(int d, t_game *g, t_player *temp);

/* Helper tool for move function */
int			ft_swap_tile(t_vector old, t_vector nw, t_game *g);

/* Re-Draws Pacmans and the floor if necessary to new position */
//void		ft_redraw(t_vector old, t_vector nw, t_game *g, int hide);
void		ft_redraw_pac(t_game *g);
void		ft_redraw_gh(t_game *g);

/* Draws walls, collectibles, and initial positions for players/enemies */
void		ft_put_map(t_game *g, int x, int y);

/* Prints ghosts on screen */
void		ft_put_ghosts(t_game *g);

/* Prints every pacman at its current state */
void		ft_put_pacman(t_game *g);

/*  */
void		ft_put_font(t_game *g, int digit, int i);

/* Iterates to animate pacman's death */
void		ft_anim_pacdeath(t_game *g);

/* Loads necessary sprites (mlx) for pacman's death */
t_list		*ft_load_pacdeath(t_game *g);

/*  */
t_font		ft_load_score_font(t_game *g);

/* Selects color for a ghost depending on the number of ghosts */
void		*ft_chooseghcolor(t_game *g, int i, int dir);

/* Loads necessary sprites for ghosts */
void		ft_load_ghosts(t_game *g);

/* Initiates sprites for every pacman */
void		ft_load_pacmans(t_game *g);

/* Frees all nodes in animation list */
void		free_animation(t_game *g);

/* Free every ghosts' sprites */
void		free_players(t_game *g);

/* Frees up, down, left, right for given player */
void		ft_free_singlepl(t_game *g, t_player *pl);

/*  */
void		free_fonts(t_game *g);

/* Updates the score that appears on screen */
void		ft_update_score(t_game *g);

/* Checks if Pacman is about to move to a ghost, initiates dath sequence */
int			ft_checkmvtogh(t_game *g, int d, t_player *pl);

/*  */
t_player	*ft_getnearestpac(t_game *g, t_player *ghost);

/*  */
void		ft_update_ghosts(t_game *g, t_player **pl);

/*  */
int			ft_findghost(t_player *pl, t_vector pos);

/*  */
void		ft_move_ghost(int d, t_game *g, t_player *ghost, t_player **pl);

/*  */
int			ft_choose_dir(t_game *g, t_player *gh, t_player *pac);

/*  */
void		ft_update_legal(t_game *g, t_player *gh);

/*  */
void		ft_restrict_legal(t_player *ghost);

/*  */
int			ft_legal_len(t_player *player);

/*  */
int			ft_reset(t_game *g);

/*  */
int			ft_in_legal(t_player *player, int dir);

/*  */
void		ft_next_dir(t_game *g);

/*  */
void		ft_delete_background(t_game *g);

#endif
