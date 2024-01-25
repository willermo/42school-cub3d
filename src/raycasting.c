/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:37:37 by afalconi          #+#    #+#             */
/*   Updated: 2024/01/24 05:20:47 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_texture_2(t_cub3d *cub3d, t_texture *tmp, double sidex, \
	double sidey)
{
	if (sidey == (int)sidey && cub3d->player->cart_y < sidey)
	{
		*tmp = cub3d->texture_west;
		cub3d->params->raycast.w_per = (sidex - (int)sidex);
	}
	if (cub3d->params->raycast.door == 1)
		*tmp = cub3d->texture_door;
}

static void	set_texture(t_cub3d *cub3d, t_texture *tmp)
{
	double	sidex;
	double	sidey;

	sidex = cub3d->params->dda.sidex;
	sidey = cub3d->params->dda.sidey;
	if (sidex == (int)sidex && cub3d->player->cart_x < sidex)
	{
		*tmp = cub3d->texture_north;
		cub3d->params->raycast.w_per = (sidey - (int)sidey);
	}
	if (sidex == (int)sidex && cub3d->player->cart_x >= sidex)
	{
		*tmp = cub3d->texture_south;
		cub3d->params->raycast.w_per = (sidey - (int)sidey);
	}
	if (sidey == (int)sidey && cub3d->player->cart_y >= sidey)
	{
		*tmp = cub3d->texture_east;
		cub3d->params->raycast.w_per = (sidex - (int)sidex);
	}
	set_texture_2(cub3d, tmp, sidex, sidey);
}

static void	render_texture(t_cub3d *c, t_texture *tmp, int x, t_image *img)
{
	t_point	start;
	t_point	end;
	double	i;
	double	scalar;
	int		coords[2];

	scalar = (double)(c->params->raycast.drowend \
		- c->params->raycast.drowstart) / (double)tmp->rows;
	i = 0.0;
	coords[0] = 0;
	coords[1] = tmp->columns * c->params->raycast.w_per;
	start.x = x;
	end.x = x;
	if (coords[1] == 0)
		coords[1] = 1;
	while (coords[0] < tmp->rows)
	{
		start.y = c->params->raycast.drowstart + (int)i;
		end.y = c->params->raycast.drowstart + (int)i + (int)scalar;
		if (start.y > 1000000000)
			break ;
		draw_line(img, start, end, tmp->array[coords[0]][coords[1]]);
		i += scalar ;
		coords[0]++;
	}
}

void	raycasting(t_cub3d *cub3d, t_image *img, int x, double tanori)
{
	int			pixel_to_rem;
	double		angles[2];
	double		corrected_wall_dis;
	t_texture	tmp;

	angles[0] = tanori * PI / 180;
	angles[1] = -cub3d->player->orientation * PI / 180;
	corrected_wall_dis = cub3d->params->raycast.wall_dis * cos(angles[0] \
		- angles[1]);
	set_texture(cub3d, &tmp);
	pixel_to_rem = (((corrected_wall_dis - cub3d->params->raycast.fov_h) \
		/ corrected_wall_dis) * SCR_H);
	cub3d->params->raycast.drowstart = pixel_to_rem / 2;
	cub3d->params->raycast.drowend = cub3d->params->raycast.drowstart \
		+ (SCR_H - pixel_to_rem);
	render_texture(cub3d, &tmp, x, img);
}
