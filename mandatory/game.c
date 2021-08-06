/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:55:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/06 10:14:16 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>

int	key_hook(int key, t_game *g)
{
	if (key == KEY_Q || key == KEY_ESC)
		end_game(g);
	if ((key == KEY_UP || key == KEY_W) && g->pl && g->pl->dir != N)
	{
		ft_newdirection(g, N);
		ft_move(N, g, &g->pl);
	}
	if ((key == KEY_DOWN || key == KEY_S) && g->pl && g->pl->dir != S)
	{
		ft_newdirection(g, S);
		ft_move(S, g, &g->pl);
	}
	if ((key == KEY_RIGHT || key == KEY_D) && g->pl && g->pl->dir != E)
	{
		ft_newdirection(g, E);
		ft_move(E, g, &g->pl);
	}
	if ((key == KEY_LEFT || key == KEY_A) && g->pl && g->pl->dir != W)
	{
		ft_newdirection(g, W);
		ft_move(W, g, &g->pl);
	}
	return (0);
}

int	end_game(t_game *g)
{
	int	i;

	if (g->map)
	{
		i = 0;
		while (g->map[i])
		{
			free(g->map[i]);
			i++;
		}
		free(g->map);
	}
	free_sprites(g);
	ft_free_playerlist(g);
	printf("%sGame Finished!\n%sTotal Moves: %d\n\n%s", GREEN, \
		BLUE, g->n_moves, DEFAULT);
	mlx_clear_window(g->id, g->w_id);
	mlx_destroy_window(g->id, g->w_id);
	free(g->id);
	exit(0);
	return (0);
}

void	init_game(char **map, t_lay *lay)
{
	t_game	g;

	g = ft_newgame(map, lay);
	mlx_loop_hook(g.id, ft_update, (void *)&g);
	mlx_hook(g.w_id, 17, 0, end_game, (void *)&g);
	mlx_key_hook(g.w_id, key_hook, (void *)&g);
	mlx_loop(g.id);
}

t_game	ft_newgame(char **map, t_lay *lay)
{
	t_game	g;

	g.n_frames = 1;
	g.n_moves = 0;
	g.width = lay->n_col * SIZE;
	g.height = lay->n_row * SIZE + 80;
	g.lay = lay;
	g.map = map;
	g.id = mlx_init();
	g.w_id = mlx_new_window(g.id, lay->n_col * SIZE, \
			lay->n_row * SIZE + 80, "Pac-Man");
	g.sprites = ft_initsprites(&g);
	g.pl = NULL;
	g.gh = NULL;
	ft_playerlist(map, &g);
	ft_load_ghosts(&g);
	ft_load_pacmans(&g);
	g.pac_dying = 0;
	g.redraw = 1;
	return (g);
}

void	ft_check_game(t_game *g)
{
	if (!(g->n_frames % GAME_RATE) && g->pl->dir != ST && !g->pac_dying)
	{
		ft_move(g->pl->dir, g, &g->pl);
		ft_update_ghosts(g, &g->pl);
	}
	if (g->pac_dying && !(g->n_frames % ANIM_RATE))
		ft_anim_pacdeath(g);
	if (!g->lay->n_collect && !g->lay->n_pl && !g->pac_dying)
	{
		printf("%sCONGRATULATIONS, YOU WIN!%s\n\n", GREEN, DEFAULT);
		end_game(g);
	}
}
