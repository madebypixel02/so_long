/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 08:57:46 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "player.h"
# include "colors.h"
# include "../mlx.h"

# define SPRITE_SIZE 32

typedef struct s_sprite
{
	void		*pacman;
	void		**wall;
	void		*pacfood;
	void		*portal;
	void		*black;
	//t_pacman	*pacman;
	//t_ghost		*ghost;
}				t_sprite;

typedef struct s_game
{
	int			width;
	int			height;
	t_lay		*lay;
	char		**map;
	void		*id;
	void		*window_id;
	int			nFrames;
	int			map_printed;
	t_sprite	sprites;
	t_player	*players;
}				t_game;

void		init_game(char **map, t_lay *lay);
t_game		ft_newgame(char **map, t_lay *lay);
int			end_game(t_game *game);
int			ft_update(t_game *game);
int			key_hook(int keycode, t_game *game);
t_sprite	ft_initsprites(t_game *game);
void		free_sprites(t_game *game);

#endif
