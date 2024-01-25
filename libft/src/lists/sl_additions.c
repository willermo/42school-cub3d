/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_additions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:48:27 by doriani           #+#    #+#             */
/*   Updated: 2024/01/11 10:23:27 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sl_add_node_begin(t_sl_list *head, t_sl_list *new_node)
{
	if (head == NULL || new_node == NULL)
		return ;
	new_node->next = head->next;
	head->next = new_node;
}

void	sl_add_node_end(t_sl_list *head, t_sl_list *new_node)
{
	register t_sl_list	*temp;

	if (head == NULL || new_node == NULL)
		return ;
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->next = NULL;
}

void	sl_add_node_by_position(t_sl_list *head, t_sl_list *new_node, int pos)
{
	register t_sl_list	*temp;
	register int		i;

	if (pos < 1 || pos > sl_size(head) + 1)
		return ;
	if (pos == 1)
		return (sl_add_node_begin(head, new_node));
	if (pos == sl_size(head) + 1)
		return (sl_add_node_end(head, new_node));
	temp = head->next;
	i = 1;
	while (i < pos - 1)
	{
		temp = temp->next;
		i++;
	}
	new_node->next = temp->next;
	temp->next = new_node;
}
