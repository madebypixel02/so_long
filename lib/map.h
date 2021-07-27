/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:36:06 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 17:50:54 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

# include "errors.h"

typedef struct s_lay
{
	int	nRow;
	int	nCol;
	int	nExits;
	int	nPlayers;
	int	nCollect;
}				t_lay;

void	ft_newlayout(t_lay *lay);
void	ft_newmap_error(t_map_err *map_err);
int		ft_print_map_error(t_map_err *map_err, char **map_str);
void	ft_readlayout(int fd, t_map_err *map_err, t_lay *lay, char **map_str);
void	ft_checklayout(char *line, t_map_err *map_err, t_lay *lay, int old_len);

#endif
