/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:26:05 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:22:23 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "mlx_utils.h"
#include <stdio.h>

void	draw_pixel(t_image *image, t_point coord, int color)
{
	char	*pixel;
	int		i;

	i = image->bits_per_pixel - 8;
	if (coord.x < 0 || coord.x >= image->width
		|| coord.y < 0 || coord.y >= image->height)
		return ;
	pixel = image->addr + (coord.y * image->line_length \
							+ coord.x * (image->bits_per_pixel / 8));
	while (i >= 0)
	{
		if (image->endian == BE)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (image->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static void	init_line_params(t_point start, t_point end, int *d, int *s)
{
	d[0] = abs(end.x - start.x);
	if (start.x < end.x)
		s[0] = 1;
	else
		s[0] = -1;
	d[1] = -abs(end.y - start.y);
	if (start.y < end.y)
		s[1] = 1;
	else
		s[1] = -1;
}

void	draw_line(t_image *image, t_point start, t_point end, int color)
{
	int	err;
	int	e2;
	int	d[2];
	int	s[2];

	init_line_params(start, end, d, s);
	err = d[0] + d[1];
	while (1)
	{
		draw_pixel(image, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 >= d[1])
		{
			err += d[1];
			start.x += s[0];
		}
		if (e2 <= d[0])
		{
			err += d[0];
			start.y += s[1];
		}
	}
}

void	draw_square(t_image *image, t_point coord, int color, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel(image, (t_point){coord.x + i, coord.y + j}, color);
			j++;
		}
		i++;
	}
}

void	draw_rectangle(t_image *image, t_point coord, int color, int size[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < size[0])
	{
		j = 0;
		while (j < size[1])
		{
			draw_pixel(image, (t_point){coord.x + i, coord.y + j}, color);
			j++;
		}
		i++;
	}
}
