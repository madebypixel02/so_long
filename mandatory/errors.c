/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:28:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 14:15:20 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	ft_newmap_error(t_map_err *map_err)
{
	map_err->inv_borders = 0;
	map_err->inv_char = 0;
	map_err->inv_nexits = 0;
	map_err->inv_ncollect = 0;
	map_err->inv_rowlen = 0;
	map_err->inv_nplayers = 0;
}

void	error_msg(char *msg, char *color, char **to_free)
{
	if (!color)
		color = DEFAULT;
	free(*to_free);
	printf("Error\n%s%s%s\n", color, msg, DEFAULT);
	exit(0);
}

void	free_matrix(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		to_free[i] = NULL;
		i++;
	}
	free(to_free);
	to_free = NULL;
}
