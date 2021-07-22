/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:36:06 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/22 22:37:10 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

typedef struct s_layout
{
	int	nrow;
	int	ncol;
	int	nexits;
	int	nplayers;
}				t_layout;

void	ft_newlayout(t_layout *lay);
int		ft_checklayout(int fd);

#endif
