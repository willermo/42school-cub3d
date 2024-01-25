/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_validation_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:02:28 by doriani           #+#    #+#             */
/*   Updated: 2024/01/18 16:22:43 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clean_mapdata(t_map *mapdata)
{
	int	i;

	i = 0;
	if (mapdata->player)
		free(mapdata->player);
	if (!mapdata)
		return (1);
	if (!mapdata->map)
	{
		free(mapdata);
		return (2);
	}
	while (i < (int) mapdata->height)
		free(mapdata->map[i++]);
	free(mapdata->map);
	free(mapdata);
	return (0);
}

char	**copy_map(t_params *params)
{
	char	**map;
	int		i;

	map = (char **) malloc(sizeof(char *) * (params->map->height));
	i = 0;
	while (i < (int) params->map->height)
	{
		map[i] = malloc(sizeof(char) * (params->map->width));
		ft_memcpy(map[i], params->map->map[i], params->map->width);
		i++;
	}
	return (map);
}

t_map	*clone_mapdata(t_params *params)
{
	t_map	*clone;

	clone = (t_map *) malloc(sizeof(t_map));
	clone->map = copy_map(params);
	clone->player = (t_player *) malloc(sizeof(t_player));
	sync_mapdata_metadata(params->map, clone);
	return (clone);
}

void	sync_mapdata_metadata(t_map *src, t_map *dest)
{
	dest->width = src->width;
	dest->height = src->height;
	dest->is_valid = src->is_valid;
	dest->player_found = src->player_found;
	dest->player_startpos[0] = src->player_startpos[0];
	dest->player_startpos[1] = src->player_startpos[1];
	dest->player_orientation = src->player_orientation;
	if (!src->player)
	{
		if (dest->player)
		{
			free(dest->player);
			dest->player = NULL;
		}
	}
	if (!dest->player && src->player)
		dest->player = (t_player *) malloc(sizeof(t_player));
	if (src->player)
	{
		dest->player->x = src->player->x;
		dest->player->y = src->player->y;
		dest->player->orientation = src->player->orientation;
		dest->player->dx = src->player->dx;
		dest->player->dy = src->player->dy;
	}
}
