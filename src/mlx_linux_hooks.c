/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_linux_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:48:11 by doriani           #+#    #+#             */
/*   Updated: 2024/01/23 13:22:12 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	keypress_main(int ks, t_cub3d *cub3d)
{
	if (ks == 0xFF1B)
	{
		mlx_loop_end(cub3d->display.mlx);
		return (0);
	}
	if (ks == 0x31)
		cub3d->gamescene = EXPLORE2D;
	if (ks == 0x32)
		cub3d->gamescene = EXPLORE3D;
	if (ks == 0x33)
		cub3d->gamescene = GAME2D;
	if (ks == 0x34)
		cub3d->gamescene = GAME3D;
	render_gamescreen(cub3d);
	return (0);
}

static int	keypress_other(int ks, t_cub3d *cub3d, int orientation)
{
	if (ks == 0x77 || ks == 0x57)
		move(cub3d, (double)orientation *(PI / 180), "up");
	if (ks == 0x61 || ks == 0x41)
		move(cub3d, (double)((orientation + 90) % 360) *(PI / 180), "left");
	if (ks == 0x73 || ks == 0x53)
		move(cub3d, (double)((orientation + 180) % 360) *(PI / 180), "down");
	if (ks == 0x64 || ks == 0x44)
		move(cub3d, (double)((orientation + 270) % 360) *(PI / 180), "right");
	if (ks == 0x20)
		activate_door(cub3d, orientation);
	if (ks == 0xff51)
		rotate(cub3d, LEFT, "Rotate left");
	if (ks == 0xff53)
		rotate(cub3d, RIGHT, "Rotate right");
	if (cub3d->gamescene == EXPLORE3D && (ks == 0x7a || ks == 0x5a))
		shoot_pistol(cub3d);
	return (0);
}

int	keypress(int ks, t_cub3d *cub3d)
{
	int	orientation;

	orientation = cub3d->player->orientation;
	if (cub3d->gamescene == MAIN)
		return (keypress_main(ks, cub3d));
	if (ks == 0xFF1B)
	{
		cub3d->gamescene = MAIN;
		render_gamescreen(cub3d);
		return (0);
	}
	return (keypress_other(ks, cub3d, orientation));
}

int	x_click(t_display *display)
{
	mlx_loop_end(display->mlx);
	return (0);
}

int	mouse_hook(int x, int y, t_cub3d *cub3d)
{
	static int	last_x = -1;
	static int	last_y = -1;

	if (cub3d->gamescene != EXPLORE2D && cub3d->gamescene != EXPLORE3D)
		return (0);
	if (last_x == -1)
		last_x = x;
	if (last_y == -1)
		last_y = y;
	if (x < last_x)
		rotate(cub3d, LEFT, "Rotate left");
	else if (x > last_x)
		rotate(cub3d, RIGHT, "Rotate right");
	last_x = x;
	last_y = y;
	return (0);
}
