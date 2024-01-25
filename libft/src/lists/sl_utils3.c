/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:59:46 by doriani           #+#    #+#             */
/*   Updated: 2024/01/12 02:49:10 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_sl_list	*sl_dup_node(t_sl_list *node, void *(*dup_data)(void *))
{
	register t_sl_list	*new_node;

	if (node == NULL)
		return (NULL);
	new_node = sl_create_node(dup_data(node->data));
	return (new_node);
}

t_sl_list	*sl_dup_node_by_position(t_sl_list *head, int position,
											void *(*dup_data)(void *))
{
	register t_sl_list	*temp;

	if (position < 1 || position > sl_size(head))
		return (NULL);
	temp = sl_get_node_by_position(head, position);
	return (sl_dup_node(temp, dup_data));
}

t_sl_list	*sl_dup_list(t_sl_list *head, void *(*dup_data)(void *))
{
	t_sl_list			*new;
	register t_sl_list	*runner;

	if (head == NULL || dup_data == NULL)
		return (NULL);
	new = sl_init_list();
	if (new == NULL)
		return (NULL);
	runner = head->next;
	while (runner != head)
	{
		sl_add_node_end(new, sl_dup_node(runner, dup_data));
		runner = runner->next;
	}
	if (sl_size(new) != sl_size(head))
	{
		sl_destroy_list(&new);
		return (NULL);
	}
	else
		return (new);
}

void	sl_foreach(t_sl_list *head, void (*f)(void *))
{
	if (head == NULL || f == NULL)
		return ;
	while (head != NULL)
	{
		f(head->data);
		head = head->next;
	}
}

t_sl_list	*sl_map(t_sl_list *head, void (*f)(void *),
					void *(*dup_data)(void *))
{
	register t_sl_list	*new;

	if (head == NULL || f == NULL)
		return (NULL);
	new = sl_dup_list(head, dup_data);
	if (new == NULL)
		return (NULL);
	sl_foreach(new, f);
	return (new);
}
