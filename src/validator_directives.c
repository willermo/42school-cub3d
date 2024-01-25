/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_directives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:13:19 by doriani           #+#    #+#             */
/*   Updated: 2024/01/14 21:21:31 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_texture_directive(char *directive)
{
	return (!ft_strcmp(directive, "NO") || !ft_strcmp(directive, "SO") \
		|| !ft_strcmp(directive, "WE") || !ft_strcmp(directive, "EA"));
}

static int	is_rgb_color_directive(char *directive)
{
	return (!ft_strcmp(directive, "F") || !ft_strcmp(directive, "C"));
}

static int	add_directive(t_params *params, char **tokens)
{
	void	*ptr;

	if (is_texture_directive(tokens[0]))
	{
		ptr = get_texture_path(params, tokens[0]);
		if (!add_texture(ptr, tokens[1], get_what(tokens[0])))
			return (0);
		return (1);
	}
	if (is_rgb_color_directive(tokens[0]))
	{
		ptr = get_rgb_color(params, tokens[0]);
		if (!add_rgb_color(ptr, tokens[1], get_what(tokens[0])))
			return (0);
		return (1);
	}
	return (0);
}

int	process_directive(t_params *params, char *line, char **tokens)
{
	if (ft_split_count(tokens) == 0)
		return (1);
	if (ft_split_count(tokens) != 2)
	{
		ft_printf("Error: invalid directive: %s\n", line);
		return (0);
	}
	return (add_directive(params, tokens));
}
