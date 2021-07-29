/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:26:18 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/29 12:42:25 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# include "colors.h"
# include <stdio.h>

void	error_msg_params(char *msg, char **map_str);
int		exit_msg(char ***map);
void	free_matrix(char ***to_free, int print);

#endif
