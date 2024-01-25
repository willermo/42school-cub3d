/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_common.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 01:03:26 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:31:50 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub3d(t_cub3d *cub3d, t_params *params)
{
	cub3d->params = params;
	cub3d->map = params->map;
	cub3d->player = params->map->player;
	cub3d->player->stats.health = PLAYER_START_HP_POINTS;
	cub3d->player->stats.mana = PLAYER_START_MANA_POINTS;
	init_system(&cub3d->display, C3D_WIDTH, C3D_HEIGHT, C3D_TITLE);
	cub3d->image = create_image(&cub3d->display, C3D_WIDTH, C3D_HEIGHT);
	cub3d->header = create_image(&cub3d->display, HDR_W, HDR_H);
	cub3d->minimap = create_image(&cub3d->display, MMP_W, MMP_H);
	cub3d->screen = create_image(&cub3d->display, SCR_W, SCR_H);
	cub3d->pistol = NULL;
	cub3d->refresh = NULL;
	cub3d->gamescene = MAIN;
	set_up_texture(cub3d);
}

void	init_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->display.win, KeyPress, KeyPressMask, keypress, cub3d);
	mlx_hook(cub3d->display.win, DestroyNotify, StructureNotifyMask, \
		x_click, &cub3d->display);
	mlx_hook(cub3d->display.win, MotionNotify, PointerMotionMask, \
		mouse_hook, cub3d);
}

static void	free_int_matrix(int **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(matrix[i++]);
	free(matrix);
}

static void	free_textures(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	while (++i < 5)
		free_int_matrix(cub3d->texture_sprite[i].array, \
			cub3d->texture_sprite[i].rows);
	free_int_matrix(cub3d->texture_north.array, cub3d->texture_north.rows);
	free_int_matrix(cub3d->texture_south.array, cub3d->texture_south.rows);
	free_int_matrix(cub3d->texture_east.array, cub3d->texture_east.rows);
	free_int_matrix(cub3d->texture_west.array, cub3d->texture_west.rows);
	free_int_matrix(cub3d->texture_door.array, cub3d->texture_door.rows);
}

void	destroy_mlx(t_cub3d *cub3d)
{
	destroy_image(&cub3d->display, cub3d->image);
	free(cub3d->image);
	destroy_image(&cub3d->display, cub3d->header);
	free(cub3d->header);
	destroy_image(&cub3d->display, cub3d->minimap);
	free(cub3d->minimap);
	destroy_image(&cub3d->display, cub3d->screen);
	free(cub3d->screen);
	if (cub3d->pistol)
	{
		destroy_image(&cub3d->display, cub3d->pistol);
		free(cub3d->pistol);
	}
	mlx_clear_window(cub3d->display.mlx, cub3d->display.win);
	mlx_destroy_window(cub3d->display.mlx, cub3d->display.win);
	mlx_destroy_display(cub3d->display.mlx);
	free(cub3d->display.mlx);
	free_textures(cub3d);
}
