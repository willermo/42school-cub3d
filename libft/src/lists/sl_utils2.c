/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:35:44 by doriani           #+#    #+#             */
/*   Updated: 2024/01/12 02:48:59 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sl_swap_list_nodes(t_sl_list *a, t_sl_list *b, \
	t_sl_list **head_a, t_sl_list **head_b)
{
	register t_sl_list	*temp_a;
	register t_sl_list	*temp_b;

	if (a == NULL || b == NULL)
		return ;
	temp_a = *head_a;
	temp_b = *head_b;
	while (temp_a->next != a)
	{
		if (temp_a->next == NULL)
			return ;
		temp_a = temp_a->next;
	}
	while (temp_b->next != b)
	{
		if (temp_b->next == NULL)
			return ;
		temp_b = temp_b->next;
	}
	temp_a->next = b;
	temp_b->next = a;
	temp_a = a->next;
	a->next = b->next;
	b->next = temp_a;
}

void	sl_swap_list_nodes_by_position(t_sl_list **head, int a, int b)
{
	register t_sl_list	*temp_a;
	register t_sl_list	*temp_b;

	if (a < 1 || a > sl_size(*head) || b < 1 || b > sl_size(*head))
		return ;
	temp_a = sl_get_node_by_position(*head, a);
	temp_b = sl_get_node_by_position(*head, b);
	sl_swap_list_nodes(temp_a, temp_b, head, head);
}

int	sl_is_sorted(t_sl_list *head, t_sort_order order,
			int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp;

	if (sl_size(head) < 2)
		return (1);
	temp = head;
	while (temp->next != NULL)
	{
		if ((order == ascending && cmp_data(temp->data, temp->next->data) > 0) \
		|| (order == descending && cmp_data(temp->data, temp->next->data) < 0))
			return (0);
		temp = temp->next;
	}
	return (1);
}
