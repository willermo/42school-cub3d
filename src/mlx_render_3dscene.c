/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_3dscene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:11:23 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:01:55 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color(int arr[3])
{
	int	color;

	color = 0;
	color += arr[0] << 16;
	color += arr[1] << 8;
	color += arr[2];
	return (color);
}

void	draw_3dscene(t_cub3d *cub3d, t_image *img, int size[2])
{
	int	floor_color;
	int	ceiling_color;
	int	halfsize[2];

	floor_color = get_color(cub3d->params->f);
	ceiling_color = get_color(cub3d->params->c);
	halfsize[0] = size[0];
	halfsize[1] = size[1] / 2;
	draw_rectangle(img, (t_point){0, 0}, ceiling_color, halfsize);
	draw_rectangle(img, (t_point){0, halfsize[1]}, floor_color, halfsize);
	dda_init(cub3d, img);
	return ;
}
