/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_draws.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:45:36 by doriani           #+#    #+#             */
/*   Updated: 2024/01/22 11:47:15 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_image *img, t_rgba color, int random, int progressive)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			if (random)
				draw_pixel(img, (t_point){j++, i}, get_random_color());
			else if (progressive)
				draw_pixel(img, (t_point){j++, i}, color++ % 0xFFFFFF);
			else
				draw_pixel(img, (t_point){j++, i}, color);
		}
		i++;
	}
}

void	draw_stats(t_cub3d *cub3d)
{
	int	j;
	int	size[2];

	j = 0;
	size[0] = STATS_BAR_LENGTH / MAX_HP_POINTS;
	size[1] = STATS_BAR_HEIGHT;
	while (j <= MAX_HP_POINTS)
	{
		if (cub3d->player->stats.health >= j)
			draw_rectangle(cub3d->refresh, (t_point){STATS_OFFSET_X + \
				j * size[0], HP_OFFSET_Y}, HP_FULL_COLOR, size);
		else
			draw_rectangle(cub3d->refresh, (t_point){STATS_OFFSET_X + \
				j * size[0], HP_OFFSET_Y}, HP_EMPTY_COLOR, size);
		if (cub3d->player->stats.mana >= j)
			draw_rectangle(cub3d->refresh, (t_point){STATS_OFFSET_X + \
				j * size[0], MANA_OFFSET_Y}, MANA_FULL_COLOR, size);
		else
			draw_rectangle(cub3d->refresh, (t_point){STATS_OFFSET_X + \
				j * size[0], MANA_OFFSET_Y}, MANA_EMPTY_COLOR, size);
		j++;
	}
}
