/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:26:18 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/23 09:51:36 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# include "colors.h"
# include <stdio.h>

int		error_msg(char *msg, char *color, char **to_free);
void	free_matrix(char **to_free);

#endif
