/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:00:02 by doriani           #+#    #+#             */
/*   Updated: 2024/01/20 16:21:41 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_player(t_cub3d *cub3d, t_image *img, int d, t_point s)
{
	t_point	p;

	p.x = cub3d->player->dy * d + (s.x - (d * cub3d->map->width)) / 2 - d / 6;
	p.y = cub3d->player->dx * d + (s.y - (d * cub3d->map->height)) / 2 - d / 6;
	draw_square(img, p, 0x0000FF, d / 3);
}

static void	draw_minimap_cell(t_image *img, int dim, t_point sizes, char cell)
{
	if (cell == '1')
		draw_square(img, sizes, 0xFF0000, dim);
	else if (ft_strchr("0NSEW", cell))
		draw_square(img, sizes, 0x00FF00, dim);
	else
		draw_square(img, sizes, 0x000000, dim);
}

void	draw_minimap(t_cub3d *cub3d, t_image *img, int size[2])
{
	unsigned int	j;
	unsigned int	i;
	int				x;
	int				y;
	unsigned int	dim;

	dim = size[1] / cub3d->map->height;
	if ((size[0] / cub3d->map->width) < dim)
		dim = size[0] / cub3d->map->width;
	i = 0;
	while (i < cub3d->map->height)
	{
		x = i * dim + (size[1] - (dim * cub3d->map->height)) / 2;
		j = 0;
		while (j < cub3d->map->width)
		{
			y = j * dim + (size[0] - (dim * cub3d->map->width)) / 2;
			draw_minimap_cell(img, dim, (t_point){y, x}, \
				cub3d->map->map[i][j]);
			j++;
		}
		draw_minimap_player(cub3d, img, dim, (t_point){size[0], size[1]});
		i++;
	}
}
