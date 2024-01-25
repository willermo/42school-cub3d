/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_removals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:10:35 by doriani           #+#    #+#             */
/*   Updated: 2024/01/12 02:48:00 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_sl_list	*sl_remove_node(t_sl_list **head, t_sl_list *node)
{
	register t_sl_list	*temp;

	if (!head || !*head || node == NULL || node->next == node)
		return (NULL);
	temp = *head;
	if (temp == node)
	{
		*head = node->next;
		node->next = NULL;
		return (node);
	}
	while (temp->next && temp->next != node)
		temp = temp->next;
	if (temp->next == NULL)
		return (NULL);
	temp->next = node->next;
	node->next = NULL;
	return (node);
}

t_sl_list	*sl_remove_node_by_position(t_sl_list **head, int pos)
{
	register t_sl_list	*temp;
	register int		i;

	if (!head || !*head || sl_is_empty(*head) \
		|| pos < 1 || pos > sl_size(*head))
		return (NULL);
	i = 0;
	temp = (*head)->next;
	while (i++ < pos)
		temp = temp->next;
	return (sl_remove_node(head, temp));
}

t_sl_list	*sl_remove_node_by_data(t_sl_list **head, void *data,
										int (cmp_data)(void *, void *))
{
	register t_sl_list	*temp;

	if (!head || !*head || sl_is_empty(*head))
		return (NULL);
	temp = (*head)->next;
	while (temp != NULL)
	{
		if (cmp_data(temp->data, data) == 0)
			return (sl_remove_node(head, temp));
		temp = temp->next;
	}
	return (NULL);
}
