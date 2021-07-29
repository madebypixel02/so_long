/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:28:25 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/29 12:50:28 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

t_err	ft_newmap_error(void)
{
	t_err	map_err;

	map_err.inv_borders = 0;
	map_err.inv_char = 0;
	map_err.inv_nExits = 0;
	map_err.inv_nCollect = 0;
	map_err.inv_rowlen = 0;
	map_err.inv_nPlayers = 0;
	return (map_err);
}

void	error_msg_params(char *msg, char **map_str)
{
	if (map_str)
		free(*map_str);
	printf("Error\n%s%s%s\n", RED, msg, DEFAULT);
	exit(0);
}

int	exit_msg(char ***map)
{
	if (map)
		free_matrix(map, 0);
	printf("Error\n%sGame Finished!%s\n", GREEN, DEFAULT);
	exit(0);
	return (0);
}

void	free_matrix(char ***to_free, int print)
{
	int	i;

	i = 0;
	while (to_free[0][i])
	{
		if (print)
			printf("%s\n", to_free[0][i]);
		free(to_free[0][i]);
		i++;
	}
	free(to_free[0]);
}
