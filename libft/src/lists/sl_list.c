/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:12:42 by doriani           #+#    #+#             */
/*   Updated: 2024/01/12 02:48:17 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_sl_list	*sl_init_list(void)
{
	register t_sl_list	*head;

	head = (t_sl_list *)malloc(sizeof(t_sl_list));
	head->data = NULL;
	head->next = NULL;
	return (head);
}

t_sl_list	*sl_create_node(void *data)
{
	register t_sl_list	*new_node;

	new_node = (t_sl_list *)malloc(sizeof(t_sl_list));
	if (new_node == NULL)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

void	sl_destroy_list(t_sl_list **head)
{
	sl_delete_list(head);
	free(*head);
	*head = NULL;
}

t_sl_list	*sl_build_list(void **array, int size)
{
	t_sl_list	*head;
	int			i;

	if (size <= 0)
		return (NULL);
	head = sl_init_list();
	i = 0;
	while (i < size)
		sl_insert_end(&head, array[i++]);
	return (head);
}

void	sl_display(t_sl_list *head, void (*display_data)(void *))
{
	register t_sl_list	*temp;

	temp = head;
	if (head == NULL)
		ft_putstr("List does not exist!");
	else if (sl_is_empty(head))
		ft_putstr("List is empty!");
	else
	{
		while (temp->next != head)
		{
			temp = temp->next;
			display_data(temp->data);
			ft_putchar(' ');
		}
	}
}

// int	sl_size(t_sl_list *lst)
// {
// 	int			i;
// 	t_sl_list	*tmp;

// 	i = 0;
// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	return (i);
// }

// void	sl_insert_begin(t_sl_list **lst, t_sl_list *new)
// {
// 	if (lst == NULL || new == NULL)
// 		return ;
// 	new->next = *lst;
// 	*lst = new;
// }

// void	sl_insert_end(t_sl_list **lst, t_sl_list *new)
// {
// 	t_sl_list	*tmp;

// 	if (lst == NULL || new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	tmp = sl_last(*lst);
// 	tmp->next = new;
// }

// t_sl_list	*sl_last(t_sl_list *lst)
// {
// 	t_sl_list	*tmp;

// 	tmp = lst;
// 	if (tmp == NULL)
// 		return (NULL);
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	return (tmp);
// }
