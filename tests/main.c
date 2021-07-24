/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:49:08 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/24 13:18:20 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int			fd;
	t_map_error	map_error;
	t_layout	layout;

	ft_newlayout(&layout);
	ft_newmap_error(&map_error);
	if (argc != 2)
		return (error_msg("Invalid number of arguments!", RED, NULL));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("File not found!", RED, NULL));
	if (ft_strrncmp(argv[1], ".ber", 4))
		return (error_msg("Invalid file type, use .ber!", RED, NULL));
	return (ft_readlayout(fd, &map_error, &layout));
}
