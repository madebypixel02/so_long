/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 11:04:35 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 20:00:15 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <mlx.h>
#include <unistd.h>

void	ft_update_score(t_game *g)
{
	int	i;
	int	score;
	int	digit;

	i = 0;
	score = g->n_moves;
	while (i < 4)
	{
		digit = score % 10;
		score /= 10;
		mlx_put_image_to_window(g->id, g->w_id, g->sprites.score_font.black, \
			g->width / 2 + 10 - 12 * i, g->height - 67);
		ft_put_font(g, digit, i);
		i++;
	}
}

t_font	ft_load_score_font(t_game *g)
{
	int	size;

	g->sprites.score_font.zero = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/0.xpm", &size, &size);
	g->sprites.score_font.one = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/1.xpm", &size, &size);
	g->sprites.score_font.two = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/2.xpm", &size, &size);
	g->sprites.score_font.three = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/3.xpm", &size, &size);
	g->sprites.score_font.four = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/4.xpm", &size, &size);
	g->sprites.score_font.five = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/5.xpm", &size, &size);
	g->sprites.score_font.six = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/6.xpm", &size, &size);
	g->sprites.score_font.seven = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/7.xpm", &size, &size);
	g->sprites.score_font.eight = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/8.xpm", &size, &size);
	g->sprites.score_font.nine = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/9.xpm", &size, &size);
	g->sprites.score_font.black = mlx_xpm_file_to_image(g->id, \
		"sprites/Other/Fonts/black.xpm", &size, &size);
	return (g->sprites.score_font);
}

void	ft_put_font(t_game *g, int digit, int i)
{
	void	*font;

	font = NULL;
	if (digit == 0)
		font = g->sprites.score_font.zero;
	if (digit == 1)
		font = g->sprites.score_font.one;
	if (digit == 2)
		font = g->sprites.score_font.two;
	if (digit == 3)
		font = g->sprites.score_font.three;
	if (digit == 4)
		font = g->sprites.score_font.four;
	if (digit == 5)
		font = g->sprites.score_font.five;
	if (digit == 6)
		font = g->sprites.score_font.six;
	if (digit == 7)
		font = g->sprites.score_font.seven;
	if (digit == 8)
		font = g->sprites.score_font.eight;
	if (digit == 9)
		font = g->sprites.score_font.nine;
	mlx_put_image_to_window(g->id, g->w_id, font, \
		g->width / 2 + 10 - 12 * i, g->height - 67);
}

void	free_fonts(t_game *g)
{
	mlx_destroy_image(g->id, g->sprites.score_font.black);
	mlx_destroy_image(g->id, g->sprites.score_font.zero);
	mlx_destroy_image(g->id, g->sprites.score_font.one);
	mlx_destroy_image(g->id, g->sprites.score_font.two);
	mlx_destroy_image(g->id, g->sprites.score_font.three);
	mlx_destroy_image(g->id, g->sprites.score_font.four);
	mlx_destroy_image(g->id, g->sprites.score_font.five);
	mlx_destroy_image(g->id, g->sprites.score_font.six);
	mlx_destroy_image(g->id, g->sprites.score_font.seven);
	mlx_destroy_image(g->id, g->sprites.score_font.eight);
	mlx_destroy_image(g->id, g->sprites.score_font.nine);
}
