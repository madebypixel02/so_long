/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:48:15 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 17:15:43 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/map.h"
#include "../libft/lib/libft.h"
#include "../lib/colors.h"
#include <stdio.h>

void	error_msg_params(char *msg, char **map_str)
{
	if (map_str)
		free(*map_str);
	printf("Error\n%s%s%s\n", RED, msg, DEFAULT);
	exit(0);
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
	int			old_len;

	line = NULL;
	last_line = NULL;
	old_len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			ft_checklayout(last_line, map_err, lay, 0);
			free(last_line);
			if (old_len == 0)
				error_msg_params("Map is empty!", NULL);
			break ;
		}
		free(last_line);
		ft_checklayout(line, map_err, lay, old_len);
		old_len = ft_strlen(line);
		last_line = ft_substr(line, 0, ft_strlen(line));
		*map_str = ft_strenlarge(*map_str, line);
		lay->n_row++;
	}
}

void	ft_checklayout(char *line, t_err *map_err, t_lay *lay, int old_len)
{
	if (old_len && old_len != (int)ft_strlen(line))
		map_err->inv_rowlen = 1;
	if (line && (line[0] != '1' || line[ft_strlen(line) - 2] != '1' || \
		(!old_len && ft_countchar(line, '1') != (int)ft_strlen(line) - 1)))
		map_err->inv_borders = 1;
	lay->n_exits += ft_countchar(line, 'E');
	lay->n_players += ft_countchar(line, 'P');
	lay->n_ghosts += ft_countchar(line, 'G');
	lay->n_collect += ft_countchar(line, 'C');
	if (!lay->n_col)
		lay->n_col = ft_strlen(line) - 1;
	map_err->inv_n_exits = lay->n_exits < 1;
	map_err->inv_n_players = lay->n_players < 1;
	map_err->inv_n_collect = lay->n_collect < 1;
	while (*line)
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
