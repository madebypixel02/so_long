/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:48:15 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/23 09:50:02 by aperez-b         ###   ########.fr       */
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

char	**ft_readlayout(int fd)
{
	char	**layout;

	layout = NULL;
	while (1)
	{
		layout = malloc(sizeof(char *));
		*layout = get_next_line(fd);
		if (!*layout)
		{
			layout = NULL;
			break ;
		
		}
		layout++;
	}
	return (layout);
}

int	ft_checklayout(char **layout)
{
	int			i;
	int			j;
	t_layout	lay;

	i = 0;
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
