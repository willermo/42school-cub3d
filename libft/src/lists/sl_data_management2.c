/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_data_management2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:58 by doriani           #+#    #+#             */
/*   Updated: 2024/01/11 10:31:43 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_sl_list	*sl_get_max_node(t_sl_list *head, int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp;
	register t_sl_list	*max;

	if (head == NULL || sl_is_empty(head))
		return (NULL);
	max = head;
	temp = max->next;
	while (temp != NULL)
	{
		if (cmp_data(temp->data, max->data) > 0)
			max = temp;
		temp = temp->next;
	}
	return (max);
}

int	sl_get_max_node_position(t_sl_list *head, int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp;
	register t_sl_list	*max;
	register int		position;
	register int		max_position;

	if (head == NULL || sl_is_empty(head))
		return (-1);
	max = head;
	max_position = 0;
	temp = max->next;
	position = 1;
	while (temp != NULL)
	{
		if (cmp_data(temp->data, max->data) > 0)
		{
			max = temp;
			max_position = position;
		}
		temp = temp->next;
		position++;
	}
	return (max_position);
}

t_sl_list	*sl_get_min_node(t_sl_list *head, int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp;
	register t_sl_list	*min;

	if (head == NULL || sl_is_empty(head))
		return (NULL);
	min = head;
	temp = min->next;
	while (temp != NULL)
	{
		if (cmp_data(temp->data, min->data) < 0)
			min = temp;
		temp = temp->next;
	}
	return (min);
}

int	sl_get_min_node_position(t_sl_list *head, int (*cmp_data)(void *, void *))
{
	register t_sl_list	*temp;
	register t_sl_list	*min;
	register int		position;
	register int		min_position;

	if (head == NULL || sl_is_empty(head))
		return (-1);
	min = head;
	min_position = 0;
	temp = min->next;
	position = 1;
	while (temp != NULL)
	{
		if (cmp_data(temp->data, min->data) < 0)
		{
			min = temp;
			min_position = position;
		}
		temp = temp->next;
		position++;
	}
	return (min_position);
}
