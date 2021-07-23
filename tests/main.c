/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:49:08 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/23 09:54:14 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	**layout;

	if (argc != 2)
		return (error_msg("Invalid number of arguments!", RED, NULL));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("File not found!", RED, NULL));
	if (ft_strrncmp(argv[1], ".ber", 4))
		return (error_msg("Invalid file type, use .ber!", RED, NULL));
	layout = ft_readlayout(fd);
	if (ft_checklayout(layout))
		return (0);
	return (0);
}
