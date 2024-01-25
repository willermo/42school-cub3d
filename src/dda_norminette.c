/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_norminette.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 04:42:43 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 05:02:33 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dda_distance(double x, double y, double x1, double y1)
{
	return (sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)));
}

void	dda_line_long(t_cub3d *cub3d)
{
	t_params	*p;
	double		x;
	double		y;
	double		sidex;
	double		sidey;

	p = cub3d->params;
	x = cub3d->player->cart_x;
	y = cub3d->player->cart_y;
	sidex = p->dda.sidex;
	sidey = p->dda.sidey;
	p->raycast.wall_dis = dda_distance(x, y, sidex, sidey);
	if (p->raycast.wall_dis < 0)
		p->raycast.wall_dis *= -1;
}
