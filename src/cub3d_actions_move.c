/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_actions_move.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:33:22 by doriani           #+#    #+#             */
/*   Updated: 2024/01/23 13:37:04 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_cub3d *cub3d, double orientation, char *move_name)
{
	double	x;
	double	y;

	x = cub3d->player->dx - PACE * cos(orientation) / CELLSIZE;
	y = cub3d->player->dy - PACE * sin(orientation) / CELLSIZE;
	if (ft_strchr("1D", cub3d->map->map[(int)x][(int)y]))
		return (print_player(cub3d->player, TY_RED_B"Wall collision"TY_RESET));
	cub3d->player->dx = x;
	cub3d->player->dy = y;
	cub3d->player->x = cub3d->player->dx * CELLSIZE;
	cub3d->player->y = cub3d->player->dy * CELLSIZE;
	print_player(cub3d->player, move_name);
	refresh(cub3d, MINIMAP, (t_point){C3D_WIDTH - C3D_WIDTH / 4, 0});
	refresh(cub3d, SCENE, (t_point){0, C3D_HEIGHT / 4});
	render_pistol(cub3d, 0);
}

void	rotate(t_cub3d *cub3d, t_rotation rotation, char *move_name)
{
	int	deg;

	if (rotation == LEFT)
		deg = ROTATION_STEP_DEGREE;
	else
		deg = -ROTATION_STEP_DEGREE;
	cub3d->player->orientation += deg + 360;
	cub3d->player->orientation %= 360;
	print_player(cub3d->player, move_name);
	refresh(cub3d, SCENE, (t_point){0, C3D_HEIGHT / 4});
	render_pistol(cub3d, 0);
}

static void	switch_door(t_cub3d *cub3d, char *cell)
{
	if (*cell == 'd')
	{
		*cell = 'D';
		print_player(cub3d->player, TY_GREEN_B"Door closed"TY_RESET);
	}
	else if (*cell == 'D')
	{
		*cell = 'd';
		print_player(cub3d->player, TY_GREEN_B"Door opened"TY_RESET);
	}
}

static void	set_direction(char *direction, int orientation)
{
	if (orientation < 45 || orientation > 315)
		*direction = 'N';
	else if (orientation >= 45 && orientation < 135)
		*direction = 'W';
	else if (orientation >= 135 && orientation < 225)
		*direction = 'S';
	else if (orientation >= 225 && orientation <= 315)
		*direction = 'E';
}

void	activate_door(t_cub3d *cub3d, int orientation)
{
	int		x;
	int		y;
	char	direction;

	x = cub3d->player->dx;
	y = cub3d->player->dy;
	set_direction(&direction, orientation);
	if (direction == 'N' && ft_strchr("Dd", cub3d->map->map[x - 1][y]))
		switch_door(cub3d, &cub3d->map->map[x - 1][y]);
	else if (direction == 'W' && ft_strchr("Dd", cub3d->map->map[x][y - 1]))
		switch_door(cub3d, &cub3d->map->map[x][y - 1]);
	else if (direction == 'S' && ft_strchr("Dd", cub3d->map->map[x + 1][y]))
		switch_door(cub3d, &cub3d->map->map[x + 1][y]);
	else if (direction == 'E' && ft_strchr("Dd", cub3d->map->map[x][y + 1]))
		switch_door(cub3d, &cub3d->map->map[x][y + 1]);
	else
		return ;
	refresh(cub3d, MINIMAP, (t_point){C3D_WIDTH - C3D_WIDTH / 4, 0});
	refresh(cub3d, SCENE, (t_point){0, C3D_HEIGHT / 4});
	render_pistol(cub3d, 0);
}
