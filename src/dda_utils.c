/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 04:33:35 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 05:07:45 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_next_int_defdinedx(t_params *params, int tan)
{
	int	side_x;

	if ((tan > 0 && tan < 90) || (tan > 270 && tan < 360))
	{
		side_x = ((int)params->dda.sidex) + 1;
	}
	else
	{
		if ((int)params->dda.sidex == params->dda.sidex)
			side_x = ((int)params->dda.sidex) - 1;
		else
			side_x = ((int)params->dda.sidex);
	}
	params->dda.sidex = side_x;
	params->dda.sidey = ((side_x - params->dda.ini_pos_x) \
		* params->dda.tanray) + params->dda.ini_pos_y ;
}

void	dda_next_int_defdixnedy(t_params *params, int tan)
{
	int	side_y;

	if (tan < 180)
	{
		side_y = ((int)params->dda.sidey) + 1;
	}
	else
	{
		if ((int)params->dda.sidey == params->dda.sidey)
			side_y = ((int)params->dda.sidey) - 1;
		else
			side_y = ((int)params->dda.sidey);
	}
	params->dda.sidey = side_y;
	params->dda.sidex = ((side_y - params->dda.ini_pos_y) / \
		params->dda.tanray) + params->dda.ini_pos_x;
}

int	right_data(t_params *params, double ex_xy, double ex_xx, \
	t_cub3d *cub3d)
{
	double	p_ex_x;
	double	p_ex_y;

	p_ex_x = dda_distance(cub3d->player->cart_x, cub3d->player->cart_y, \
		ex_xx, ex_xy);
	p_ex_y = dda_distance(cub3d->player->cart_x, cub3d->player->cart_y, \
		params->dda.sidex, params->dda.sidey);
	if (p_ex_x < 0)
		p_ex_x *= -1;
	if (p_ex_y < 0)
		p_ex_y *= -1;
	if (p_ex_x < p_ex_y)
		return (1);
	return (0);
}

static void	set_xy(int *x, int *y, t_params *params, int tan)
{
	if (tan > 0 && tan < 90)
	{
		*x = (int)params->dda.ini_pos_x;
		*y = (int)params->dda.ini_pos_y;
	}
	else if (tan > 90 && tan < 180)
	{
		*y = (int)params->dda.ini_pos_y;
		*x = (int)params->dda.sidex;
	}
	else if (tan > 180 && tan < 270)
	{
		*x = (int)params->dda.sidex;
		*y = (int)params->dda.sidey;
	}
	else if (tan > 270 && tan < 360)
	{
		*y = (int)params->dda.sidey;
		*x = (int)params->dda.ini_pos_x;
	}
}

int	dda_in_map(t_params *params, int tan)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	set_xy(&x, &y, params, tan);
	if (params->map->inverted_map[x][y] == 'D')
		params->raycast.door = 1;
	else
		params->raycast.door = 0;
	if (ft_strchr("0NEWSd", params->map->inverted_map[x][y]))
		return (0);
	return (1);
}
