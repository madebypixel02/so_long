/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:48:15 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/22 22:58:14 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

void	ft_newlayout(t_layout *lay)
{
	lay->nrow = 0;
	lay->ncol = 0;
	lay->nexits = 0;
	lay->nplayers = 0;
}

int	ft_checklayout(int fd)
{
	char		*row;
	t_layout	lay;

	ft_newlayout(&lay);
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		lay.nrow++;
		if (!lay.ncol)
			lay.ncol = ft_strlen(row);
		else if (lay.ncol != (int)ft_strlen(row))
		{
			free(row);
			return (error_msg("Rows aren't the same length!", RED));
		}
		free(row);
	}
	if (lay.nexits != 1 || lay.nplayers != 1)
		return (error_msg("Map doesn't follow requirements! \
								(exits: 1, players: 1)", RED));
	return (0);
}
