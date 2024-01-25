/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:16:44 by doriani           #+#    #+#             */
/*   Updated: 2024/01/18 18:40:20 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "mlx_utils.h"

t_image	*create_image(t_display *display, int width, int height)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->width = width;
	image->height = height;
	image->img = mlx_new_image(display->mlx, image->width, image->height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return (image);
}

t_image	*load_xpm_image(t_display *display, char *path)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->img = mlx_xpm_file_to_image(display->mlx, path,
			&image->width, &image->height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return (image);
}

void	add_image(t_display *display, t_image *image, t_point p)
{
	mlx_put_image_to_window(display->mlx, display->win, image->img, p.x, p.y);
}

void	destroy_image(t_display *display, t_image *image)
{
	mlx_destroy_image(display->mlx, image->img);
}

void	clear_image(t_display *display, t_image **image)
{
	t_image	*tmp;
	int		w;
	int		h;

	tmp = *image;
	w = tmp->width;
	h = tmp->height;
	destroy_image(display, *image);
	create_image(display, w, h);
	tmp->img = mlx_new_image(display->mlx, w, h);
	tmp->addr = mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel,
			&tmp->line_length, &tmp->endian);
}
