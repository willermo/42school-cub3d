/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_deletions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:31:53 by doriani           #+#    #+#             */
/*   Updated: 2024/01/12 02:39:55 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sl_delete_begin(t_sl_list **head)
{
	register t_sl_list	*temp;

	if (head == NULL || *head == NULL)
		return ;
	temp = *head;
	*head = (*head)->next;
	free(temp->data);
	temp->data = NULL;
	free(temp);
}

void	sl_delete_end(t_sl_list **head)
{
	register t_sl_list	*temp;

	if (head == NULL || *head == NULL)
		return ;
	if (sl_size(*head) == 1)
		return (sl_delete_begin(head));
	temp = *head;
	while (temp->next->next != NULL)
		temp = temp->next;
	free(temp->next->data);
	temp->next->data = NULL;
	free(temp->next);
	temp->next = NULL;
}

void	sl_delete_node(t_sl_list **head, t_sl_list *node)
{
	register t_sl_list	*temp;

	if (head == NULL || *head == NULL || node == NULL)
		return ;
	temp = *head;
	while (temp->next != node)
		temp = temp->next;
	temp->next = node->next;
	free(node->data);
	node->data = NULL;
	free(node);
}

void	sl_delete_node_by_position(t_sl_list **head, int position)
{
	register t_sl_list	*temp;
	register int		i;

	if (!head || !*head || position < 0 || position > sl_size(*head) - 1)
		return ;
	if (position == 0)
		return (sl_delete_begin(head));
	if (position == sl_size(*head) - 1)
		return (sl_delete_end(head));
	temp = *head;
	i = 0;
	while (i++ < position)
		temp = temp->next;
	sl_delete_node(head, temp);
}

void	sl_delete_list(t_sl_list **head)
{
	if (head == NULL || *head == NULL)
		return ;
	while (*head)
		sl_delete_begin(head);
}
