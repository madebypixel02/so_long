/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:55:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/03 20:52:11 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

int	key_hook(int key, t_game *g)
{
	if (key == KEY_Q || key == KEY_ESC)
		end_game(g);
	if ((key == KEY_UP || key == KEY_W) && g->pl->dir != N)
	{
		ft_newdirection(g, N);
		move(&g->map, N, g);
	}
	if ((key == KEY_DOWN || key == KEY_S) && g->pl->dir != S)
	{
		ft_newdirection(g, S);
		move(&g->map, S, g);
	}
	if ((key == KEY_RIGHT || key == KEY_D) && g->pl->dir != E)
	{
		ft_newdirection(g, E);
		move(&g->map, E, g);
	}
	if ((key == KEY_LEFT || key == KEY_A) && g->pl->dir != W)
	{
		ft_newdirection(g, W);
		move(&g->map, W, g);
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
	printf("%sGame Finished!%s\n", GREEN, DEFAULT);
	mlx_clear_window(g->id, g->w_id);
	mlx_destroy_window(g->id, g->w_id);
	mlx_destroy_display(g->id);
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
	g.n_moves = 1;
	g.width = lay->n_col * SIZE;
	g.height = lay->n_row * SIZE + OFFSET;
	g.lay = lay;
	g.map = map;
	g.id = mlx_init();
	g.w_id = mlx_new_window(g.id, lay->n_col * SIZE, \
			lay->n_row * SIZE + 100, "Pac-Man");
	g.sprites = ft_initsprites(&g);
	g.pl = NULL;
	g.gh = NULL;
	ft_playerlist(map, &g);
	g.redraw = 1;
	g.pac_dying = 0;
	g.pac_moving = 0;
	g.g_rate = 4000;
	g.anim_rate = 1200;
	return (g);
}
