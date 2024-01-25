/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:54:48 by doriani           #+#    #+#             */
/*   Updated: 2024/01/12 16:47:26 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	*runner;

	runner = (char *) s;
	while (*runner)
	{
		if (*runner == (char) c)
			return (runner);
		runner++;
	}
	if (*runner == (char) c)
		return (runner);
	return (NULL);
}
