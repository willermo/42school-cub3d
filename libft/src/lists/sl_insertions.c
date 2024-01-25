/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_insertions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:56:53 by doriani           #+#    #+#             */
/*   Updated: 2024/01/13 12:12:39 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sl_insert_begin(t_sl_list **head, void *data)
{
	register t_sl_list	*new_node;

	if (head == NULL || *head == NULL)
		return ;
	new_node = sl_create_node(data);
	if (new_node)
	{
		new_node->next = (*head)->next;
		(*head)->next = new_node;
	}
}

void	sl_insert_end(t_sl_list **head, void *data)
{
	register t_sl_list	*new_node;
	register t_sl_list	*temp;

	if (head == NULL || *head == NULL)
		return ;
	temp = *head;
	new_node = sl_create_node(data);
	if (new_node)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	sl_insert_by_position(t_sl_list **head, void *data, int position)
{
	register t_sl_list	*new_node;
	register t_sl_list	*temp;
	register int		i;

	if (!head || !*head || position < 0 || position > sl_size(*head))
		return ;
	if (position == 0)
		return (sl_insert_begin(head, data));
	if (position == sl_size(*head))
		return (sl_insert_end(head, data));
	new_node = sl_create_node(data);
	if (new_node == NULL)
		return ;
	temp = *head;
	i = 0;
	while (i++ < position - 1)
		temp = temp->next;
	new_node->next = temp->next;
	temp->next = new_node;
}
