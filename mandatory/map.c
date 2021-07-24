/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:48:15 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/24 21:15:43 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	ft_newlayout(t_lay *lay)
{
	lay->nrow = 0;
	lay->ncol = 0;
	lay->nexits = 0;
	lay->nplayers = 0;
	lay->ncollect = 0;
}

int	ft_readlayout(int fd, t_map_err *map_err, t_lay *lay)
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
			if (ft_countchar(last_line, '1') != (int)ft_strlen(last_line) - 1)
				map_err->inv_borders = 1;
			if (last_line)
				free(last_line);
			if (!old_len)
				return (error_msg("Map is empty!", RED, NULL));
			break ;
		}
		free(last_line);
		ft_checklayout(line, map_err, lay, old_len);
		old_len = ft_strlen(line);
		last_line = ft_substr(line, 0, ft_strlen(line));
		free(line);
	}
	return (ft_print_map_error(map_err));
}

void	ft_checklayout(char *line, t_map_err *map_err, t_lay *lay, int old_len)
{
	if (old_len && old_len != (int)ft_strlen(line))
		map_err->inv_rowlen = 1;
	if ((!old_len && ft_countchar(line, '1') != (int)ft_strlen(line) - 1) \
		|| line[0] != '1' || line[ft_strlen(line) - 2] != '1')
		map_err->inv_borders = 1;
	lay->nexits += ft_countchar(line, 'E');
	lay->nplayers += ft_countchar(line, 'P');
	lay->ncollect += ft_countchar(line, 'C');
	if (!lay->ncol)
		lay->ncol = ft_strlen(line) - 1;
	lay->nrow++;
	map_err->inv_nexits = lay->nexits != 1;
	map_err->inv_nplayers = lay->nplayers != 1;
	map_err->inv_ncollect = lay->ncollect < 1;
	if (ft_countchar(line, '0') + ft_countchar(line, '1') + \
		ft_countchar(line, 'C') + ft_countchar(line, 'E') + \
		ft_countchar(line, 'P') != ((int)ft_strlen(line) - 1))
		map_err->inv_char = 1;
}

int	ft_print_map_error(t_map_err *map_err)
{
	if (map_err->inv_borders)
		error_msg("Map must be surrounded by borders!", RED, NULL);
	if (map_err->inv_rowlen)
		error_msg("Map must be rectangular!", RED, NULL);
	if (map_err->inv_char)
		error_msg("Unexpected char(s) in map!", RED, NULL);
	if (map_err->inv_nexits)
		error_msg("Invalid number of exits!", RED, NULL);
	if (map_err->inv_nplayers)
		error_msg("Invalid number of players!", RED, NULL);
	if (map_err->inv_ncollect)
		error_msg("There should be at least one collectible!", RED, NULL);
	return (0);
}
