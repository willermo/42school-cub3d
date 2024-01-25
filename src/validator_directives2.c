/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_directives2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:08:12 by doriani           #+#    #+#             */
/*   Updated: 2024/01/14 21:12:16 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_texture_path(t_params *params, char *directive)
{
	char	**path_ptr;

	path_ptr = NULL;
	if (!ft_strcmp(directive, "NO"))
		path_ptr = &params->no_path;
	if (!ft_strcmp(directive, "SO"))
		path_ptr = &params->so_path;
	if (!ft_strcmp(directive, "WE"))
		path_ptr = &params->we_path;
	if (!ft_strcmp(directive, "EA"))
		path_ptr = &params->ea_path;
	return (path_ptr);
}

int	*get_rgb_color(t_params *params, char *directive)
{
	int	*rgb_color_ptr;

	rgb_color_ptr = NULL;
	if (!ft_strcmp(directive, "F"))
		rgb_color_ptr = params->f;
	if (!ft_strcmp(directive, "C"))
		rgb_color_ptr = params->c;
	return (rgb_color_ptr);
}

char	*get_what(char *directive)
{
	if (!ft_strcmp(directive, "NO"))
		return ("North texture file");
	if (!ft_strcmp(directive, "SO"))
		return ("South texture file");
	if (!ft_strcmp(directive, "WE"))
		return ("West texture file");
	if (!ft_strcmp(directive, "EA"))
		return ("East texture file");
	if (!ft_strcmp(directive, "F"))
		return ("Floor RGB values");
	if (!ft_strcmp(directive, "C"))
		return ("Ceil RGB values");
	return (NULL);
}

int	add_texture(char **path, char *token, const char *what)
{
	if (*path)
	{
		ft_printf("Error: trying to redefine %s file\n", what);
		return (0);
	}
	if (!ft_access(token, O_RDONLY))
	{
		ft_printf("Error opening %s %s : %s\n", what, token, strerror(errno));
		return (0);
	}
	*path = ft_strdup(token);
	return (1);
}

int	add_rgb_color(int *rgb_color, char *token, const char *what)
{
	char	**rgb;

	if (rgb_color[0] >= 0)
	{
		ft_printf("Error: trying to redefine %s color\n", what);
		return (0);
	}
	rgb = ft_split(token, ",");
	if (!ft_strisnum(rgb[0]) || !ft_strisnum(rgb[1]) || !ft_strisnum(rgb[2]))
	{
		ft_printf("Error: invalid %s color: %s\n", what, token);
		ft_split_clean(rgb);
		return (0);
	}
	rgb_color[0] = ft_atoi(rgb[0]);
	rgb_color[1] = ft_atoi(rgb[1]);
	rgb_color[2] = ft_atoi(rgb[2]);
	ft_split_clean(rgb);
	return (1);
}
