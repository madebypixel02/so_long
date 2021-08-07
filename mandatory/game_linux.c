/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_linux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 21:38:26 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/08 00:08:57 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"
#include <mlx.h>

int	key_hook(int key, t_game *g)
{
	if ((key == KEY_Q || key == KEY_ESC) && !g->pac_dying)
		end_game(g);
	if (key == KEY_R && !g->pac_dying)
		ft_reset(g);
	if ((key == KEY_UP || key == KEY_W) && g->next_dir != N)
		ft_newdirection(g, N);
	if ((key == KEY_DOWN || key == KEY_S) && g->next_dir != S)
		ft_newdirection(g, S);
	if ((key == KEY_RIGHT || key == KEY_D) && g->next_dir != E)
		ft_newdirection(g, E);
	if ((key == KEY_LEFT || key == KEY_A) && g->next_dir != W)
		ft_newdirection(g, W);
	return (0);
}

int	end_game(t_game *g)
{
	if (g->map)
		ft_free_matrix(&g->map);
	if (g->map_bak)
		ft_free_matrix(&g->map_bak);
	free_sprites(g);
	ft_free_playerlist(g);
	printf("%sGame Finished!\n%sTotal Moves: %d\n\n%s", GREEN, \
		BLUE, g->n_moves, DEFAULT);
	mlx_clear_window(g->id, g->w_id);
	mlx_destroy_window(g->id, g->w_id);
	mlx_destroy_display(g->id);
	free(g->id);
	exit(0);
	return (0);
}

void	init_game(char **map, t_lay lay)
{
	t_game	g;

	g.lay_bak = lay;
	g.n_collect_bak = lay.n_collect;
	g.map_bak = ft_dup_matrix(map);
	g.id = mlx_init();
	g.w_id = mlx_new_window(g.id, lay.n_col * SIZE, \
		lay.n_row * SIZE + 80, "Pac-Man");
	ft_newgame(&g, map, &lay);
}

void	ft_newgame(t_game *g, char **m, t_lay *lay)
{
	g->n_frames = 1;
	g->n_moves = 0;
	g->width = lay->n_col * SIZE;
	g->height = lay->n_row * SIZE + 80;
	g->lay = lay;
	g->map = m;
	g->sprites = ft_initsprites(g);
	g->pl = NULL;
	g->gh = NULL;
	ft_playerlist(m, g);
	g->next_dir = 0;
	ft_load_ghosts(g);
	ft_load_pacmans(g);
	g->pac_dying = 0;
	g->panic_mode = 0;
	g->g_rate = GAME_RATE - (30 * lay->n_row) - (30 * lay->n_col);
	g->redraw = 1;
	mlx_loop_hook(g->id, ft_update, (void *)g);
	mlx_hook(g->w_id, 17, 0, end_game, (void *)g);
	mlx_key_hook(g->w_id, key_hook, (void *)g);
	mlx_loop(g->id);
}

void	ft_check_game(t_game *g)
{
	if (g->lay_bak.n_collect / 4 + 1 >= g->lay->n_collect)
	{
		if (!g->panic_mode)
			g->g_rate -= g->g_rate / 4;
		g->panic_mode = 1;
	}
	if (!(g->n_frames % g->g_rate) && g->next_dir && !g->pac_dying)
		ft_next_dir(g);
	if (!(g->n_frames % (g->g_rate + g->g_rate / 20)) \
			&& g->pl->dir != ST && !g->pac_dying)
		ft_update_ghosts(g, &g->pl);
	if (g->pac_dying && !(g->n_frames % ANIM_RATE))
		ft_anim_pacdeath(g);
	if (!g->lay->n_collect && !g->lay->n_pl && !g->pac_dying)
	{
		printf("%sCONGRATULATIONS, YOU WIN!%s\n\n", GREEN, DEFAULT);
		end_game(g);
	}
}
