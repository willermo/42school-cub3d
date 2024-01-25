/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:57:46 by doriani           #+#    #+#             */
/*   Updated: 2024/01/12 02:45:35 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sl_size(t_sl_list *head)
{
	register t_sl_list	*temp;
	register int		count;

	if (head == NULL)
		return (0);
	temp = head;
	count = 1;
	while (temp->next != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	sl_is_empty(t_sl_list *head)
{
	if (head == NULL)
		return (1);
	return (0);
}

void	sl_reverse(t_sl_list **head)
{
	register t_sl_list	*new;

	if (!head || !*head || sl_size(*head) < 2)
		return ;
	new = sl_init_list();
	while (*head != NULL)
	{
		sl_add_node_begin(new, sl_remove_node_by_position(head, 0));
	}
	sl_destroy_list(head);
	*head = new;
}

void	sl_sort(t_sl_list **head, t_sort_order order,
				int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp1;
	register t_sl_list	*temp2;

	if (!head || !*head || sl_size(*head) < 2)
		return ;
	temp1 = *head;
	while (temp1->next)
	{
		temp2 = temp1->next;
		while (temp2 != NULL)
		{
			if ((cmp_data(temp1->data, temp2->data) > 0 && order == ascending) \
			|| (cmp_data(temp1->data, temp2->data) < 0 && order == descending))
			{
				sl_swap_list_nodes(temp1, temp2, head, head);
				temp1 = temp2;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
}
