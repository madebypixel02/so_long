/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:33:55 by aperez-b          #+#    #+#             */
/*   Updated: 2021/08/04 10:34:39 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

int	ft_delete_player(t_vector old, t_player **pl)
{
	t_player	*temp;
	t_player	*prev;

	temp = *pl;
	prev = NULL;
	while (temp)
	{
		if (temp->pos.x == old.x && temp->pos.y == old.y)
		{
			if (!prev)
				return (ft_deletefirst_plr(pl));
			if (prev && !temp->next)
				return (ft_deletelast_plr(pl));
			prev->next = temp->next;
			free(temp);
			temp = NULL;
			return (1);
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	return (1);
}

int	ft_deletefirst_plr(t_player **pl)
{
	t_player	*head;

	head = *pl;
	if (head->next)
		*pl = head->next;
	else
		*pl = NULL;
	free(head);
	head = NULL;
	return (1);
}

int	ft_deletelast_plr(t_player **pl)
{
	t_player	*head;

	head = *pl;
	while (head->next->next)
		head = head->next;
	free(head->next);
	head->next = NULL;
	return (1);
}
