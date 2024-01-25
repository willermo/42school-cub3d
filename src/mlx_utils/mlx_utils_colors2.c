/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_colors2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:26:58 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:14:08 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_utils.h"
#include <time.h>
#include <stdlib.h>

t_rgba	get_random_color(void)
{
	srand(time(NULL));
	return (rand() % 0xFFFFFF);
}

int	get_pixel_color(t_image *image, int x, int y)
{
	char	*pixel;

	pixel = image->addr \
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (*(int *)pixel);
}

int	blend(int src, int dst, double alpha)
{
	int	r;
	int	g;
	int	b;

	r = (1 - alpha) * ((src >> 16) & 0xFF) + alpha * ((dst >> 16) & 0xFF);
	g = (1 - alpha) * ((src >> 8) & 0xFF) + alpha * ((dst >> 8) & 0xFF);
	b = (1 - alpha) * (src & 0xFF) + alpha * (dst & 0xFF);
	return ((r << 16) | (g << 8) | b);
}
