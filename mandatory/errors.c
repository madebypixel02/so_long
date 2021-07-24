/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:28:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/24 21:09:12 by aperez-b         ###   ########.fr       */
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

int	error_msg(char *msg, char *color, char **to_free)
{
	if (!color)
		color = DEFAULT;
	if (to_free)
		free_matrix(to_free);
	printf("Error\n%s%s%s\n", color, msg, DEFAULT);
	return (0);
}

void	free_matrix(char **to_free)
{
	while (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
		to_free++;
	}
	free(to_free);
	to_free = NULL;
}
