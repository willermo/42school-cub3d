/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:37:07 by afalconi          #+#    #+#             */
/*   Updated: 2024/01/24 05:00:22 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dda_90(t_cub3d *cub3d, t_params *p, int tan)
{
	if (tan == 0)
		p->dda.sidex = ceil(cub3d->player->cart_x);
	if (tan == 90)
		p->dda.sidey = ceil(cub3d->player->cart_y);
	if (tan == 180)
		p->dda.sidex = floor(cub3d->player->cart_x);
	if (tan == 270)
		p->dda.sidey = floor(cub3d->player->cart_y);
}

void	dda_90(t_cub3d *cub3d, int tan)
{
	t_params	*p;
	char		c;

	p = cub3d->params;
	init_dda_90(cub3d, p, tan);
	c = p->map->inverted_map[(int)p->dda.sidex][(int)p->dda.sidey];
	while (ft_strchr("0NSEWd", c))
	{
		if (tan == 0)
			p->dda.sidex += 1.0;
		else if (tan == 90)
			p->dda.sidey += 1.0;
		else if (tan == 180)
			p->dda.sidex -= 1.0;
		else if (tan == 270)
			p->dda.sidey -= 1.0;
		c = p->map->inverted_map[(int)p->dda.sidex][(int)p->dda.sidey];
	}
	if (tan == 180)
		p->dda.sidex += 1;
	else if (tan == 270)
		p->dda.sidey += 1;
}

static void	init_dda_next_int(double *init_pos, double *tmp, t_cub3d *cub3d, \
	double tan)
{
	init_pos[0] = cub3d->params->dda.sidex;
	init_pos[1] = cub3d->params->dda.sidey;
	dda_next_int_defdinedx(cub3d->params, (int)tan);
	tmp[0] = cub3d->params->dda.sidex;
	tmp[1] = cub3d->params->dda.sidey;
	cub3d->params->dda.sidey = init_pos[1];
	cub3d->params->dda.sidex = init_pos[0];
	dda_next_int_defdixnedy(cub3d->params, (int)tan);
}

static void	dda_next_int(t_cub3d *cub3d, double tan)
{
	double	init_pos[2];
	double	tmp[2];

	if ((tan >= 0.0 && tan < 1.0) || (tan >= 90.0 && tan < 91.0) \
		|| (tan >= 180.0 && tan < 181.0) || (tan >= 270.0 && tan < 271.0))
	{
		dda_90(cub3d, (int)tan);
		return ;
	}
	while (1)
	{
		init_dda_next_int(init_pos, tmp, cub3d, tan);
		if (right_data(cub3d->params, tmp[1], tmp[0], cub3d))
		{
			cub3d->params->dda.sidex = tmp[0];
			cub3d->params->dda.sidey = tmp[1];
		}
		if (dda_in_map(cub3d->params, (int)tan))
			break ;
		cub3d->params->dda.ini_pos_x = cub3d->params->dda.sidex;
		cub3d->params->dda.ini_pos_y = cub3d->params->dda.sidey;
	}
	cub3d->params->dda.sidex = cub3d->params->dda.ini_pos_x;
	cub3d->params->dda.sidey = cub3d->params->dda.ini_pos_y;
}

void	dda_init(t_cub3d *cub3d, t_image *img)
{
	int				x;
	double			tanori;
	double			scalar;

	cub3d->player->cart_y = cub3d->player->dy;
	cub3d->player->cart_x = cub3d->map->height - cub3d->player->dx;
	x = -1;
	tanori = (-cub3d->player->orientation - FOV_W / 2 + 720) % 360;
	scalar = FOV_W / (double) SCR_W;
	cub3d->params->raycast.fov_h = 0.5 / tan(FOV_H * PI / 180);
	while (++x < SCR_W)
	{
		cub3d->params->dda.tanray = tan(tanori * PI / 180);
		cub3d->params->dda.sidex = cub3d->player->cart_x;
		cub3d->params->dda.sidey = cub3d->player->cart_y;
		cub3d->params->dda.ini_pos_x = cub3d->params->dda.sidex;
		cub3d->params->dda.ini_pos_y = cub3d->params->dda.sidey;
		dda_next_int(cub3d, tanori);
		dda_line_long(cub3d);
		raycasting(cub3d, img, x, tanori);
		tanori = tanori + scalar;
		if (tanori >= 360)
			tanori -= 360;
	}
}
