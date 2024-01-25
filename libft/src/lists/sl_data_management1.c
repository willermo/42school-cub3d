/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_data_management1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:23:38 by doriani           #+#    #+#             */
/*   Updated: 2024/01/11 10:29:55 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*sl_get_node_data(t_sl_list *node)
{
	if (node == NULL)
		return (NULL);
	return (node->data);
}

void	*sl_get_node_data_by_position(t_sl_list *head, int position)
{
	register t_sl_list	*temp;
	register int		i;

	if (position < 0 || position > sl_size(head))
		return (NULL);
	temp = head;
	i = 0;
	while (i < position)
	{
		temp = temp->next;
		i++;
	}
	return (temp->data);
}

void	sl_set_node_data(t_sl_list *node, void *data)
{
	if (node == NULL)
		return ;
	if (node->data != NULL)
		free(node->data);
	node->data = data;
}

void	sl_set_node_data_by_position(t_sl_list *head, void *data,
											int position)
{
	register t_sl_list	*temp;
	register int		i;

	if (position < 0 || position > sl_size(head))
		return ;
	temp = head;
	i = 0;
	while (i < position)
	{
		temp = temp->next;
		i++;
	}
	if (temp->data != NULL)
		free(temp->data);
	temp->data = data;
}
