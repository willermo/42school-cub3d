/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:45:31 by afalconi          #+#    #+#             */
/*   Updated: 2024/01/24 05:10:13 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_up_texture(t_cub3d *cub3d)
{
	parser_xpm(&cub3d->texture_north, cub3d->params->no_path);
	parser_xpm(&cub3d->texture_east, cub3d->params->ea_path);
	parser_xpm(&cub3d->texture_south, cub3d->params->so_path);
	parser_xpm(&cub3d->texture_west, cub3d->params->we_path);
	parser_xpm(&cub3d->texture_door, DOOR_TEXTURE);
	parser_xpm(&cub3d->texture_sprite[0], PISTOL_TEXTURE_0);
	parser_xpm(&cub3d->texture_sprite[1], PISTOL_TEXTURE_1);
	parser_xpm(&cub3d->texture_sprite[2], PISTOL_TEXTURE_2);
	parser_xpm(&cub3d->texture_sprite[3], PISTOL_TEXTURE_3);
	parser_xpm(&cub3d->texture_sprite[4], PISTOL_TEXTURE_4);
}
