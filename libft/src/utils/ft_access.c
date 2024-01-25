/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:57:55 by doriani           #+#    #+#             */
/*   Updated: 2024/01/14 14:18:38 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

int	ft_access(char *path, int mode)
{
	int	fd;

	fd = open(path, mode);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
