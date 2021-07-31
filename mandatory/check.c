/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:45:11 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/31 10:29:20 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/check.h"

void	error_msg_params(char *msg, char **map_str);

t_lay	ft_newlayout(void)
{
	t_lay	lay;

	lay.n_row = 0;
	lay.n_col = 0;
	lay.n_exits = 0;
	lay.n_players = 0;
	lay.n_ghosts = 0;
	lay.n_collect = 0;
	return (lay);
}

char	**check_params(int argc, char **argv, t_lay *lay)
{
	int		fd;

	if (argc != 2)
		error_msg_params("Invalid number of arguments!", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_msg_params("File not found!", NULL);
	if (ft_strrncmp(argv[1], ".ber", 4))
		error_msg_params("Invalid file type, use .ber!", NULL);
	return (check_map(fd, lay));
}

char	**check_map(int fd, t_lay *lay)
{
	char	*map_str;
	char	**map;
	t_err	map_err;

	map_str = NULL;
	map = NULL;
	map_err = ft_newmap_error();
	*lay = ft_newlayout();
	ft_readlayout(fd, &map_err, lay, &map_str);
	ft_print_map_error(&map_err, &map_str);
	map = ft_split(map_str, '\n');
	free(map_str);
	if (!map)
	{
		error_msg_params("Memory allocation error!", NULL);
		return (0);
	}
	return (map);
}
