/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:28:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 17:47:31 by aperez-b         ###   ########.fr       */
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

void	error_msg(char *msg, char *color, char **to_free)
{
	if (!color)
		color = DEFAULT;
	if (to_free)
		free(*to_free);
	printf("Error\n%s%s%s\n", color, msg, DEFAULT);
	exit(0);
}

void	free_matrix(char ***to_free)
{
	int	i;

	i = 0;
	while (to_free[0][i])
	{
		free(to_free[0][i]);
		i++;
	}
	free(to_free[0]);
}
