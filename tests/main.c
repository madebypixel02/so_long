/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:49:08 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/24 21:08:25 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int			fd;
	t_map_err	map_err;
	t_lay		lay;

	ft_newlayout(&lay);
	ft_newmap_error(&map_err);
	if (argc != 2)
		return (error_msg("Invalid number of arguments!", RED, NULL));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("File not found!", RED, NULL));
	if (ft_strrncmp(argv[1], ".ber", 4))
		return (error_msg("Invalid file type, use .ber!", RED, NULL));
	return (ft_readlayout(fd, &map_err, &lay));
}
