/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:31 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:04:34 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_refresh3(t_cub3d *cub3d, t_component comp, t_image ***ptr)
{
	if (comp == MINIMAP)
	{
		*ptr = &cub3d->minimap;
		if (cub3d->gamescene == MAIN || cub3d->gamescene > EXPLORE3D)
			cub3d->refresh = load_xpm_image(&cub3d->display, XPM_LOGO42);
		else
		{
			cub3d->refresh = create_image(&cub3d->display, MMP_W, MMP_H);
			draw_minimap(cub3d, cub3d->refresh, (int [2]){MMP_W, MMP_H});
		}
	}
}

static void	setup_refresh2(t_cub3d *cub3d, t_component comp, t_image ***ptr)
{
	if (comp == SCENE)
	{
		*ptr = &cub3d->screen;
		if (cub3d->gamescene == MAIN)
			cub3d->refresh = load_xpm_image(&cub3d->display, XPM_MAIN_SCENE);
		else if (cub3d->gamescene == EXPLORE2D)
		{
			cub3d->refresh = create_image(&cub3d->display, SCR_W, SCR_H);
			draw_minimap(cub3d, cub3d->refresh, (int [2]){SCR_W, SCR_H});
		}
		else if (cub3d->gamescene == EXPLORE3D)
		{
			cub3d->refresh = create_image(&cub3d->display, SCR_W, SCR_H);
			draw_3dscene(cub3d, cub3d->refresh, (int [2]){SCR_W, SCR_H});
		}
		else
			cub3d->refresh = load_xpm_image(&cub3d->display, XPM_WIP);
	}
	else
		setup_refresh3(cub3d, comp, ptr);
}

static void	setup_refresh(t_cub3d *cub3d, t_component comp, t_image ***ptr)
{
	if (comp == SCREEN)
	{
		*ptr = &cub3d->image;
		cub3d->refresh = create_image(&cub3d->display, C3D_WIDTH, C3D_HEIGHT);
		draw_background(cub3d->refresh, 0x0000FF, 0, 0);
	}
	else if (comp == HEADER)
	{
		*ptr = &cub3d->header;
		if (cub3d->gamescene != EXPLORE2D)
			cub3d->refresh = load_xpm_image(&cub3d->display, XPM_HEADER);
		else
		{
			cub3d->refresh = load_xpm_image(&cub3d->display, XPM_PLAYERSTATS);
			draw_stats(cub3d);
		}
	}
	else
		setup_refresh2(cub3d, comp, ptr);
}

void	refresh(t_cub3d *cub3d, t_component component, t_point coords)
{
	t_image	**ptr;

	setup_refresh(cub3d, component, &ptr);
	add_image(&cub3d->display, cub3d->refresh, coords);
	destroy_image(&cub3d->display, *ptr);
	free(*ptr);
	*ptr = cub3d->refresh;
	cub3d->refresh = NULL;
}

void	render_gamescreen(t_cub3d *cub3d)
{
	refresh(cub3d, HEADER, (t_point){0, 0});
	refresh(cub3d, MINIMAP, (t_point){600, 0});
	refresh(cub3d, SCENE, (t_point){0, 200});
	if (cub3d->gamescene == EXPLORE3D)
		render_pistol(cub3d, 0);
}
