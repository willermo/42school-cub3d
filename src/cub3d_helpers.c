/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 05:44:18 by doriani           #+#    #+#             */
/*   Updated: 2024/01/17 23:18:45 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_map_directives(t_params *p)
{
	ft_printf(TY_CYAN_U"Map directives"TY_RESET"\n");
	ft_printf("  North texture path: %s\n", p->no_path);
	ft_printf("  South texture path: %s\n", p->so_path);
	ft_printf("  West texture path: %s\n", p->we_path);
	ft_printf("  East texture path: %s\n", p->ea_path);
	ft_printf("  Floor RGB color: %d,%d,%d\n", p->f[0], p->f[1], p->f[2]);
	ft_printf("  Ceil RGB color: %d, %d, %d\n", p->c[0], p->c[1], p->c[2]);
}

static void	print_map_data(t_params *p)
{
	ft_printf(TY_CYAN_U"Map data"TY_RESET"\n");
	ft_printf("  Map width: %d\n", p->map->width);
	ft_printf("  Map height: %d\n", p->map->height);
	if (!p->map->is_valid)
	{
		ft_printf("  Map is not valid\n");
		return ;
	}
	ft_printf("  Map is valid\n");
	if (!p->map->player_found)
	{
		ft_printf("  Player not found\n");
		return ;
	}
	ft_printf("  Player found @%d,%d oriented %c\n", \
		p->map->player_startpos[0], p->map->player_startpos[1], \
		p->map->player_orientation);
}

void	print_player(t_player *player, char *title)
{
	ft_printf("\n"TY_LIGHT_GREY_K"%s"TY_RESET"\n", title);
	ft_printf("  Player orientation: %d\n", player->orientation);
	printf("  Player position (doubles): %f,%f\n", player->dx, \
		(float)player->dy);
	printf("  Player position (scaled int): %d,%d\n", \
		player->x, player->y);
	printf("  Player position (map cells): %d,%d\n", \
		player->x / CELLSIZE, player->y / CELLSIZE);
}

void	print_session_summary(t_params *p)
{
	print_map_directives(p);
	print_map_data(p);
	ft_printf("\n"TY_LIGHT_GREY_K"Map"TY_RESET"\n");
	print_map(p->map);
	print_player(p->map->player, "Player status");
}
