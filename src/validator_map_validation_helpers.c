/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_validation_helpers.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:58:28 by doriani           #+#    #+#             */
/*   Updated: 2024/01/17 23:18:45 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cell_is_valid(t_map *map, int i, int j)
{
	if (i < 0 || i >= (int) map->height || j < 0 || j >= (int) map->width || \
		map->map[i][j] == ' ')
		return (0);
	return (1);
}

static int	neighborhood_is_valid(t_map *map, int i, int j)
{
	if (cell_is_valid(map, i + 1, j) && \
		cell_is_valid(map, i - 1, j) && \
		cell_is_valid(map, i, j + 1) && \
		cell_is_valid(map, i, j - 1))
		return (1);
	return (0);
}

static void	set_orientation(t_player *player, char orientation)
{
	if (orientation == 'N')
		player->orientation = 0;
	else if (orientation == 'W')
		player->orientation = 90;
	else if (orientation == 'S')
		player->orientation = 180;
	else if (orientation == 'E')
		player->orientation = 270;
	else
	{
		ft_printf(TY_RED"\nError: Unknown player orientation (%c)\n"TY_RESET, \
			orientation);
		ft_printf(TY_RED"Exiting cub3d\n"TY_RESET);
		exit(0);
	}
}

static void	set_player(t_map *map, int i, int j)
{
	if (map->player_found)
	{
		ft_printf(TY_RED"\nError: Duplicate player @(%d,%d)\n"TY_RESET, i, j);
		ft_printf(TY_RED"Player is already defined @(%d,%d)\n"TY_RESET, \
			map->player_startpos[0], map->player_startpos[1]);
		map->is_valid = 0;
		map->map[i][j] = '!';
		return ;
	}
	map->player_found = 1;
	map->player_startpos[0] = i;
	map->player_startpos[1] = j;
	map->player_orientation = map->map[i][j];
	map->player = (t_player *) malloc(sizeof(t_player));
	map->player->x = CELLSIZE * i + CELLSIZE / 2;
	map->player->y = CELLSIZE * j + CELLSIZE / 2;
	map->player->dx = (double) map->player->x / CELLSIZE;
	map->player->dy = (double) map->player->y / CELLSIZE;
	set_orientation(map->player, map->player_orientation);
}

int	test_cell(t_map *map, int i, int j)
{
	if (!cell_is_valid(map, i, j))
	{
		ft_printf(TY_RED"\nError: Out of map exploration\n"TY_RESET);
		map->is_valid = 0;
		return (0);
	}
	if (ft_strchr("1*", map->map[i][j]))
		return (0);
	if (ft_strchr("NSEW", map->map[i][j]))
		set_player(map, i, j);
	if (!neighborhood_is_valid(map, i, j))
	{
		ft_printf(TY_RED"\nError: Map not closed @(%d,%d)\n"TY_RESET, i, j);
		map->is_valid = 0;
		map->map[i][j] = '!';
		return (0);
	}
	return (1);
}
