/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:36:06 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/23 19:59:57 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

# include "errors.h"

typedef struct s_layout
{
	int	nrow;
	int	ncol;
	int	nexits;
	int	nplayers;
}				t_layout;

void	ft_newlayout(t_layout *lay);
void	ft_newmap_error(t_map_error *map_error);
int		ft_print_map_error(t_map_error *map_error);
int		ft_readlayout(int fd, t_map_error *map_error);

#endif
