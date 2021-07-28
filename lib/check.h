/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:52:18 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/28 19:44:53 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H

# define CHECK_H

# include "errors.h"
# include <fcntl.h>
# include "../libft/lib/libft.h"

t_tile	**check_params(int argc, char **argv);
t_tile	**check_map(int fd);

#endif
