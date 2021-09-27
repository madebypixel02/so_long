/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:49:08 by aperez-b          #+#    #+#             */
/*   Updated: 2021/09/27 20:00:40 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../inc/check.h"
#include "../inc/game.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	**map;
	t_lay	lay;

	map = check_params(argc, argv, &lay);
	init_game(map, lay);
	return (0);
}
