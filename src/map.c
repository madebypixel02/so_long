/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:48:15 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 19:59:29 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"
#include "../libft/inc/libft.h"
#include "../inc/colors.h"
#include <stdio.h>

int	error_msg_params(char *msg, char **map_str)
{
	if (map_str)
		free(*map_str);
	printf("Error\n%s%s%s\n", RED, msg, DEFAULT);
	exit(0);
	return (0);
}

t_err	ft_newmap_error(void)
{
	t_err	map_err;

	map_err.inv_borders = 0;
	map_err.inv_char = 0;
	map_err.inv_n_exits = 0;
	map_err.inv_n_collect = 0;
	map_err.inv_rowlen = 0;
	map_err.inv_n_players = 0;
	map_err.inv_n_ghosts = 0;
	return (map_err);
}

void	ft_readlayout(int fd, t_err *map_err, t_lay *lay, char **map_str)
{
	char		*line;
	char		*last_line;

	line = NULL;
	last_line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (!lay->n_col)
				error_msg_params("Map is empty!", NULL);
			else
				ft_checklayout(last_line, map_err, lay, 1);
			free(last_line);
			break ;
		}
		free(last_line);
		ft_checklayout(line, map_err, lay, !lay->n_row);
		last_line = ft_substr(line, 0, ft_strlen(line));
		*map_str = ft_strenlarge(*map_str, line);
		lay->n_row++;
	}
}

void	ft_checklayout(char *line, t_err *map_err, t_lay *lay, int is_last)
{
	if (!lay->n_col)
		lay->n_col = ft_strlen(line) - 1;
	if (lay->n_col && ((lay->n_col != (int)ft_strlen(line) - 1 && \
			ft_strchr(line, '\n')) || (lay->n_col != (int)ft_strlen(line) && \
			!ft_strchr(line, '\n'))))
		map_err->inv_rowlen = 1;
	if (line[0] != '1' || line[lay->n_col - 1] != '1' || \
			(ft_countchar(line, '1') != lay->n_col && is_last))
		map_err->inv_borders = 1;
	lay->n_exit += ft_countchar(line, 'E');
	lay->n_pl += ft_countchar(line, 'P');
	lay->n_gh += ft_countchar(line, 'G');
	lay->n_collect += ft_countchar(line, 'C');
	map_err->inv_n_exits = lay->n_exit < 1;
	map_err->inv_n_players = lay->n_pl < 1;
	map_err->inv_n_collect = lay->n_collect < 1;
	while (line && *line)
	{
		if (!ft_strchr("01CEPG\n", *line))
			map_err->inv_char = 1;
		line++;
	}
}

int	ft_print_map_error(t_err *map_err, char **map_str)
{
	if (map_err->inv_rowlen)
		error_msg_params("Map must be rectangular!", map_str);
	if (map_err->inv_borders)
		error_msg_params("Map must be surrounded by walls!", map_str);
	if (map_err->inv_char)
		error_msg_params("Unexpected char(s) in map!", map_str);
	if (map_err->inv_n_exits)
		error_msg_params("Invalid number of exits!", map_str);
	if (map_err->inv_n_players)
		error_msg_params("Invalid number of players!", map_str);
	if (map_err->inv_n_collect)
		error_msg_params("There should be at least one collectible!", map_str);
	return (0);
}
