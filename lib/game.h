/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 22:31:01 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "tile.h"
# include "vector.h"

//# define SPRITE_SIZE 64 
# define SPRITE_SIZE 64

typedef struct s_mlx
{
	void	*id;
	void	*window_id;
	void	*hook_id;
}				t_mlx;

typedef struct s_game
{
	t_vector	wndw_size;
	t_tile		**tilemap;
	t_mlx		mlx;
}				t_game;

void	init_game(t_tile **tilemap, t_lay *lay);
t_mlx	start_mlx(t_lay lay);
t_game	ft_newgame(t_tile **tilemap, t_lay lay);
void	print_tilemap(t_game *game);

#endif
