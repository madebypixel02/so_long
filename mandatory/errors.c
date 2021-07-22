/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:28:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/22 18:39:08 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/errors.h"

int	error_msg(char *msg, char *color)
{
	if (!color)
		color = DEFAULT;
	printf("%sError\n%s%s\n", color, msg, DEFAULT);
	return (0);
}
