/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/30 11:41:26 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "player.h"
# include "colors.h"

# define SPRITE_SIZE 64

typedef struct s_game
{
	int			width;
	int			height;
	char		**map;
	void		*id;
	void		*window_id;
	int			nFrames;
	t_player	*players;
}				t_game;

void	init_game(char **map, t_lay *lay);
t_game	ft_newgame(char **map, t_lay lay);
int		end_game(t_game *game);
int		ft_update(t_game *game);
int		key_hook(int keycode, t_game *game);

#endif
