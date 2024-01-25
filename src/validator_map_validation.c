/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 21:28:46 by doriani           #+#    #+#             */
/*   Updated: 2024/01/23 11:42:33 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*next_starting_coordinates(t_map *map)
{
	int	*coordinates;
	int	i;
	int	j;

	if (!map->is_valid)
		return (NULL);
	coordinates = (int *) malloc(sizeof(int) * 2);
	i = 0;
	while (i < (int) map->height)
	{
		j = 0;
		while (j < (int) map->width)
		{
			if (ft_strchr("NSEW0dD", map->map[i][j]))
			{
				coordinates[0] = i;
				coordinates[1] = j;
				return (coordinates);
			}
			j++;
		}
		i++;
	}
	free(coordinates);
	return (NULL);
}

static void	explore_map(t_map *map, int i, int j)
{
	if (!map->is_valid || !test_cell(map, i, j))
		return ;
	map->map[i][j] = '*';
	if (map->is_valid)
		explore_map(map, i - 1, j);
	if (map->is_valid)
		explore_map(map, i + 1, j);
	if (map->is_valid)
		explore_map(map, i, j - 1);
	if (map->is_valid)
		explore_map(map, i, j + 1);
	return ;
}

static void	process_coordinates(t_map *mapdata, int **coordinates)
{
	int	i;

	i = 0;
	while (*coordinates && mapdata->is_valid)
	{
		explore_map(mapdata, (*coordinates)[0], (*coordinates)[1]);
		if (VERBOSE && mapdata->is_valid)
		{
			ft_printf(TY_LIGHT_GREY_K"Floodfill stage %d"TY_RESET"\n", i++);
			print_map(mapdata);
		}
		else if (!mapdata->is_valid)
		{
			ft_printf(TY_LIGHT_GREY_K"Error detection map"TY_RESET"\n");
			print_map(mapdata);
		}
		free(*coordinates);
		*coordinates = next_starting_coordinates(mapdata);
	}
}

int	validate_map(t_params *params)
{
	t_map	*mapdata;
	int		*coordinates;

	if (!params->map)
		return (ft_printf(TY_RED"Error: No map found\n"TY_RESET), 0);
	mapdata = clone_mapdata(params);
	coordinates = next_starting_coordinates(mapdata);
	process_coordinates(mapdata, &coordinates);
	if (coordinates)
		free(coordinates);
	if (mapdata->is_valid)
	{
		mapdata->is_valid = 1;
		sync_mapdata_metadata(mapdata, params->map);
		return (clean_mapdata(mapdata), 1);
	}
	sync_mapdata_metadata(mapdata, params->map);
	return (clean_mapdata(mapdata), 0);
}
