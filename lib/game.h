/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:56:05 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/29 13:15:32 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "map.h"
# include "vector.h"
# include "colors.h"

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
	char		**map;
	t_mlx		mlx;
	int			nFrames;
}				t_game;

void	init_game(char **map, t_lay *lay);
t_mlx	start_mlx(t_lay lay);
t_game	ft_newgame(char **map, t_lay lay);
void	free_matrix(char ***to_free, int print);
int		exit_msg(t_game *game);
int		print_map(t_game *game);
void	end_game();

#endif
