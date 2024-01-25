/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_pistol.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:53:44 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:09:22 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_pistol(t_cub3d *cub3d, int frame)
{
	cub3d->refresh = create_image(&cub3d->display, SPR_W, SPR_H);
	draw_pistol(cub3d, cub3d->refresh, frame);
	add_image(&cub3d->display, cub3d->refresh, (t_point){SPR_X, SPR_Y});
	if (cub3d->pistol)
	{
		destroy_image(&cub3d->display, cub3d->pistol);
		free(cub3d->pistol);
	}
	cub3d->pistol = cub3d->refresh;
	cub3d->refresh = NULL;
}

void	draw_pistol(t_cub3d *cub3d, t_image *image, int frame)
{
	int			x;
	int			y;
	int			color;
	t_texture	texture;

	texture = cub3d->texture_sprite[frame];
	x = 0;
	while (x < texture.columns)
	{
		y = 0;
		while (y < texture.rows)
		{
			color = texture.array[x][y];
			if (color >= 0)
				draw_pixel(image, (t_point){y, x}, color);
			else
				draw_pixel(image, (t_point){y, x}, \
					get_pixel_color(cub3d->screen, \
					SCR_W / 2 - SPR_W / 2 + y, SCR_H - SPR_H + x));
			y++;
		}
		x++;
	}
}

void	shoot_pistol(t_cub3d *cub3d)
{
	int	frame;

	frame = 0;
	while (frame < 5)
	{
		render_pistol(cub3d, frame++);
		usleep(100000);
	}
	render_pistol(cub3d, 0);
}
