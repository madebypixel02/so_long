/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:36:06 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 19:32:07 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

typedef struct s_lay
{
	int	nRow;
	int	nCol;
	int	nExits;
	int	nPlayers;
	int	nCollect;
}				t_lay;

typedef struct s_err
{
	int	inv_rowlen;
	int	inv_char;
	int	inv_nPlayers;
	int	inv_nCollect;
	int	inv_nExits;
	int	inv_borders;
}				t_err;

t_lay	ft_newlayout(void);
t_err	ft_newmap_error(void);
int		ft_print_map_error(t_err *map_err, char **map_str);
void	ft_readlayout(int fd, t_err *map_err, t_lay *lay, char **map_str);
void	ft_checklayout(char *line, t_err *map_err, t_lay *lay, int old_len);

#endif
