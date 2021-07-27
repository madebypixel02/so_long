/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 18:56:18 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/26 21:10:40 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H

# define VECTOR_H

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef enum e_direction
{
	STOP = 0,
	NORTH = 1,
	SOUTH = -1,
	EAST = 2,
	WEST = -2
}			t_direction;

#endif
