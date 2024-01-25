/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:23:14 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:30:21 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_params(t_params *params)
{
	params->no_path = NULL;
	params->so_path = NULL;
	params->we_path = NULL;
	params->ea_path = NULL;
	params->f[0] = -1;
	params->f[1] = -1;
	params->f[2] = -1;
	params->c[0] = -1;
	params->c[1] = -1;
	params->c[2] = -1;
	params->map = (t_map *) malloc(sizeof(t_map));
	params->map->map = NULL;
	params->map->width = 0;
	params->map->height = 0;
	params->map->is_valid = -1;
	params->map->player_found = 0;
	params->map->player_startpos[0] = -1;
	params->map->player_startpos[1] = -1;
	params->map->player_orientation = '\0';
	params->map->player = NULL;
}

int	parse_mapfile(char *mapfile, t_params *params)
{
	int	mapfile_fd;

	if (!validate_mapfile_name(&mapfile_fd, mapfile))
		return (0);
	if (!validate_directives(mapfile_fd, params)
		|| !validate_mapdata(mapfile_fd, params))
	{
		close(mapfile_fd);
		return (0);
	}
	close(mapfile_fd);
	return (1);
}

void	start_cub3d(char *mapfile, t_params *params)
{
	t_cub3d	cub3d;

	ft_printf("\n"TY_BLUE_K" Starting cub3d. Mapfile: %s"TY_RESET"\n", mapfile);
	print_session_summary(params);
	init_cub3d(&cub3d, params);
	render_gamescreen(&cub3d);
	init_hooks(&cub3d);
	mlx_loop(cub3d.display.mlx);
	destroy_mlx(&cub3d);
}

static void	clean_map(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->map[i])
		{
			free(map->map[i]);
			map->map[i] = NULL;
		}
		i++;
	}
}

void	clean_params(t_params *params)
{
	if (params->no_path)
		free(params->no_path);
	if (params->so_path)
		free(params->so_path);
	if (params->we_path)
		free(params->we_path);
	if (params->ea_path)
		free(params->ea_path);
	if (params->map->map)
	{
		clean_map(params->map);
		free(params->map->map);
	}
	if (params->map->inverted_map)
		free(params->map->inverted_map);
	if (params->map->player)
		free(params->map->player);
	free(params->map);
}
