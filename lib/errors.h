/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:26:18 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/24 20:53:43 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# include "colors.h"
# include <stdio.h>

typedef struct s_map_err
{
	int	inv_rowlen;
	int	inv_char;
	int	inv_nplayers;
	int	inv_ncollect;
	int	inv_nexits;
	int	inv_borders;
}				t_map_err;

int		error_msg(char *msg, char *color, char **to_free);
void	free_matrix(char **to_free);

#endif
