/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:28:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 10:57:19 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	ft_newmap_error(t_map_err *map_err)
{
	map_err->inv_borders = 0;
	map_err->inv_char = 0;
	map_err->inv_nExits = 0;
	map_err->inv_nCollect = 0;
	map_err->inv_rowlen = 0;
	map_err->inv_nPlayers = 0;
}

void	error_msg(char *msg, char **map_str, t_tile ***tilemap)
{
	if (map_str)
		free(*map_str);
	if (tilemap)
		free_tilemap(tilemap, 0);
	printf("Error\n%s%s%s\n", RED, msg, DEFAULT);
	exit(0);
}

t_tile	**error_msg_tile(char *msg, t_tile ***tilemap)
{
	if (tilemap)
		free_tilemap(tilemap, 0);
	printf("Error\n%s%s%s\n", RED, msg, DEFAULT);
	exit(0);
	return (NULL);
}

void	free_matrix(char ***to_free, int print)
{
	int	i;

	i = 0;
	while (to_free[0][i])
	{
		if (print)
			printf("%s\n", to_free[0][i]);
		free(to_free[0][i]);
		i++;
	}
	free(to_free[0]);
}
