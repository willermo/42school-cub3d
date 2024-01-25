/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_searches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:20:25 by doriani           #+#    #+#             */
/*   Updated: 2024/01/11 11:22:49 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sl_get_node_position(t_sl_list *head, void *data,
								int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp;
	register int		position;

	if (head == NULL || head->next == NULL)
		return (0);
	temp = head;
	position = 0;
	while (temp != head)
	{
		if (cmp_data(temp->data, data) == 0)
			return (position);
		temp = temp->next;
		position++;
	}
	return (0);
}

t_sl_list	*sl_get_node_by_position(t_sl_list *head, int pos)
{
	register t_sl_list	*temp;
	register int		i;

	if (pos < 0 || pos >= sl_size(head) || head == NULL || sl_is_empty(head))
		return (NULL);
	temp = head->next;
	i = 0;
	while (i++ < pos)
		temp = temp->next;
	return (temp);
}

t_sl_list	*sl_get_node_by_data(t_sl_list *head, void *data,
									int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp;

	if (head == NULL || head->next == NULL)
		return (NULL);
	temp = head;
	while (temp != NULL)
	{
		if (cmp_data(temp->data, data) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
