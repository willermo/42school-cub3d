/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:58:07 by doriani           #+#    #+#             */
/*   Updated: 2024/01/17 23:21:07 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "mlx_utils.h"

void	init_system(t_display *display, int width, int height, char *title)
{
	display->mlx = mlx_init();
	display->win = mlx_new_window(display->mlx, width, height, title);
}

int	get_endianness(void)
{
	int		i;
	char	*str;

	i = 1;
	str = (char *)&i;
	if (*str)
		return (LE);
	else
		return (BE);
}
