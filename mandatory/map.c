/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:48:15 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/24 14:31:55 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	ft_newlayout(t_layout *lay)
{
	lay->nrow = 0;
	lay->ncol = 0;
	lay->nexits = 0;
	lay->nplayers = 0;
	lay->ncollectibles = 0;
}

void	ft_newmap_error(t_map_error *map_error)
{
	map_error->inv_borders = 0;
	map_error->inv_char = 0;
	map_error->inv_nexits = 0;
	map_error->inv_ncollectibles = 0;
	map_error->inv_rowlen = 0;
	map_error->inv_nplayers = 0;
}

int	ft_readlayout(int fd, t_map_error *map_error, t_layout *layout)
{
	char		*line;
	int			line_len;
	int			i;

	line = NULL;
	line_len = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_len && line_len != (int)ft_strlen(line))
			map_error->inv_rowlen = 1;
		line_len = ft_strlen(line);
		if ((!i && ft_countchar(line, '1') != line_len - 1) \
			|| line[0] != '1' || line[line_len - 2] != '1')
			map_error->inv_borders = 1;
		ft_check_layout(line, map_error, layout);
		free(line);
		i++;
	}
	return (ft_print_map_error(map_error));
}

void	ft_check_layout(char *line, t_map_error *map_error, t_layout *layout)
{
	layout->nexits += ft_countchar(line, 'E');
	layout->nplayers += ft_countchar(line, 'P');
	layout->ncollectibles += ft_countchar(line, 'C');
	if (!layout->ncol)
		layout->ncol = ft_strlen(line) - 1;
	layout->nrow++;
	map_error->inv_nexits = layout->nexits != 1;
	map_error->inv_nplayers = layout->nplayers != 1;
	map_error->inv_ncollectibles = layout->ncollectibles < 1;
	if (ft_countchar(line, '0') + ft_countchar(line, '1') + \
		ft_countchar(line, 'C') + ft_countchar(line, 'E') + \
		ft_countchar(line, 'P') != ((int)ft_strlen(line) - 1))
		map_error->inv_char = 1;
}

int	ft_print_map_error(t_map_error *map_error)
{
	if (map_error->inv_borders)
		error_msg("Map must be surrounded by borders!", RED, NULL);
	if (map_error->inv_rowlen)
		error_msg("Map must be rectangular!", RED, NULL);
	if (map_error->inv_char)
		error_msg("Unexpected char(s) in map!", RED, NULL);
	if (map_error->inv_nexits)
		error_msg("Invalid number of exits!", RED, NULL);
	if (map_error->inv_nplayers)
		error_msg("Invalid number of players!", RED, NULL);
	if (map_error->inv_ncollectibles)
		error_msg("There should be at least one collectible!", RED, NULL);
	return (0);
}
