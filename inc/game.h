/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 19:58:26 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "colors.h"
# include "../libft/inc/libft.h"
# include <mlx.h>
# include <stdio.h>

/* Sprite Size */
# define SIZE 32

/* Ghost color order:
 * (R)ed, (B)lue, Pin(K), (O)range, (G)reen, (Y)ellow, (P)urple */
# define COLORS "RBKOGYP"

/* Enum for (ST)op, (N)orth, (S)outh, (E)ast, (W)est as ints */
enum e_direction
{
	ST = 0,
	N = 1,
	S = -1,
	E = 2,
	W = -2
};

/* Struct to store the sprites for every digit */
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

/* Struct containing list of sprites for a given player */
typedef struct s_pl_sprite
{
	t_list	*up;
	t_list	*up_bak;
	t_list	*down;
	t_list	*down_bak;
	t_list	*left;
	t_list	*left_bak;
	t_list	*right;
	t_list	*right_bak;
	t_list	*panic;
	t_list	*panic_bak;
}				t_pl_sprite;

/* MLX image pointers for the map */
typedef struct s_sprite
{
	void		*logo;
	void		**wall;
	void		*pacfood;
	void		*portal;
	void		*pacman;
	void		*pixels;
	void		*black;
	t_list		*pac_dying_bak;
	t_list		*pac_dying;
	t_font		score_font;
}				t_sprite;

/* Small list showing if a player can go north, south, east or west */
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
	void		*id;
	void		*w_id;
	t_lay		*lay;
	t_lay		lay_bak;
	t_sprite	sprites;
	t_player	*pl;
	t_player	*gh;
	int			next_dir;
	char		**map;
	char		**map_bak;
	int			n_collect_bak;
	int			pac_dying;
	int			panic_mode;
	int			n_frames;
	int			n_moves;
	int			redraw;
	int			g_rate;
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

/* Redraws All pacmans to a new position and/or direction */
void		ft_redraw_pac(t_game *g);

/* Redraws All ghosts to a new position and/or direction */
void		ft_redraw_gh(t_game *g);

/* Redraws a pacdot in a given position (in case a ghost goes over a pacdot) */
void		ft_redraw_pacfood(t_game *g, t_player *pl);

/* Redraws an exit in a given position (in case a ghost goes over an exit) */
void		ft_redraw_exit(t_game *g, t_player *pl);

/* Draws walls, collectibles, and initial positions for players/enemies */
void		ft_put_map(t_game *g, int x, int y);

/* Prints ghosts on screen */
void		ft_put_ghosts(t_game *g);

/* Prints every pacman at its current state */
void		ft_put_pacman(t_game *g);

/* Draws the current moves with the retro pacman font */
void		ft_put_font(t_game *g, int digit, int i);

/* Iterates to animate pacman's death */
void		ft_anim_pacdeath(t_game *g);

/* Loads necessary sprites (mlx) for pacman's death */
t_list		*ft_load_pacdeath(t_game *g);

/* Loads necessary sprites (mlx) to draw the score */
t_font		ft_load_score_font(t_game *g);

/* Selects color for a ghost depending on the number of ghosts */
t_list		*ft_chooseghcolor(t_game *g, int i, int dir);

/* Loads necessary sprites for ghosts */
void		ft_load_ghosts(t_game *g);

/* Initiates sprites for every pacman */
void		ft_load_pacmans(t_game *g);

/* Frees all nodes in animation list */
void		free_animation(t_game *g, t_list *start);

/* Free every ghosts' sprites */
void		free_players(t_game *g);

/* Frees up, down, left, right for given player */
void		ft_free_singlepl(t_game *g, t_player *pl);

/* Frees font-related sprites */
void		free_fonts(t_game *g);

/* Updates the score that appears on screen */
void		ft_update_score(t_game *g);

/* Checks if Pacman is about to move to a ghost, initiates dath sequence */
int			ft_checkmvtogh(t_game *g, int d, t_player *pl);

/* Uses euclidean distance to retrieve the closest pacman from a given ghost */
t_player	*ft_getnearestpac(t_game *g, t_player *ghost);

/* Updates every ghosts' position to try and catch a pacman */
void		ft_update_ghosts(t_game *g);

/* Checks if there's a ghost in the given position */
int			ft_findghost(t_player *pl, t_vector pos);

/* Change ghosts' direction if possible */
void		ft_move_ghost(int d, t_game *g, t_player *ghost);

/* Simple algorithm to find the optimal direction to take to get a pacman */
int			ft_choose_dir(t_game *g, t_player *gh, t_player *pac);

/* When there are multiple options, get the shortest to a pacman */
int			ft_advanced_dir(t_player *gh, t_player *pac, int *distances);

/* Aux function for east and west options */
int			ft_advanced_dir2(int *distances);

/* Checks if there's a ghost, exit or wall to update a ghost's legal actions */
void		ft_update_legal(t_game *g, t_player *gh);

/* If north available restrict south, if east available restrict west, etc */
void		ft_restrict_legal(t_player *ghost);

/* Counts the number of available actions for a given player */
int			ft_legal_len(t_player *player);

/* Resets and frees everything needed to start a new game */
int			ft_reset(t_game *g);

/* Checks if a direction is in the legal actions for a player */
int			ft_in_legal(t_player *player, int dir);

/* Changes pacmans' directions to target direction if possible */
void		ft_next_dir(t_game *g);

/* Loads necessary sprites to move north */
t_list		*ft_load_north(t_game *g, char *path, int i);

/* Loads necessary sprites to move south */
t_list		*ft_load_south(t_game *g, char *path, int i);

/* Loads necessary sprites to move east */
t_list		*ft_load_east(t_game *g, char *path, int i);

/* Loads necessary sprites to move west */
t_list		*ft_load_west(t_game *g, char *path, int i);

/* Loads necessary sprites to animate panic mode for ghosts */
t_list		*ft_load_panic(t_game *g, int i);

/* Changes sprites to animate moving north */
void		ft_anim_north(t_game *g, t_player *pl);

/* Changes sprites to animate moving south */
void		ft_anim_south(t_game *g, t_player *pl);

/* Changes sprites to animate moving east */
void		ft_anim_east(t_game *g, t_player *pl);

/* Changes sprites to animate moving west */
void		ft_anim_west(t_game *g, t_player *pl);

/* Changes sprites to animate ghosts while in panic mode */
void		ft_anim_panic(t_game *g, t_player *pl);

/* Puts the default sprite for a given direction when a player isn't moving */
void		ft_put_stopped(t_game *g, t_player *pl);

#endif
