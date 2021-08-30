/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:36:06 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/30 13:15:11 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

# include <stdlib.h>
# include "../get_next_line/get_next_line.h"

/* Struct to store and handle layout properties */
typedef struct s_lay
{
	int	n_row;
	int	n_col;
	int	n_exit;
	int	n_pl;
	int	n_gh;
	int	n_collect;
}				t_lay;

/* Struct to handle all possible layout errors */
typedef struct s_err
{
	int	inv_rowlen;
	int	inv_char;
	int	inv_n_players;
	int	inv_n_ghosts;
	int	inv_n_collect;
	int	inv_n_exits;
	int	inv_borders;
}				t_err;

/* Creates new layout with all attributes set to zero */
t_lay	ft_newlayout(void);

/* Creates new map error struct and sets attributes to zero */
t_err	ft_newmap_error(void);

/* Checks map error struct to print an error and exit the game */
int		ft_print_map_error(t_err *map_err, char **map_str);

/* Uses get_next_line to check errors and builds a string of the map */
void	ft_readlayout(int fd, t_err *map_err, t_lay *lay, char **map_str);

/* Checks a given line to handle errors on it */
void	ft_checklayout(char *line, t_err *map_err, t_lay *lay, int is_last);

/* Prints a custom error message and exits the program */
int		error_msg_params(char *msg, char **map_str);

#endif
