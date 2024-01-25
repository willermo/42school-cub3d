/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:13:31 by doriani           #+#    #+#             */
/*   Updated: 2024/01/17 23:08:47 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_mapfile_name(int *fd, char *mapfile)
{
	int	len;

	len = ft_strlen(mapfile);
	ft_printf(TY_YELLOW_B"\nValidating mapfile: %s\n"TY_RESET, mapfile);
	if (len < 5 || ft_strcmp(mapfile + len - 4, ".cub"))
	{
		ft_printf("Error: Invalid mapfile name\n");
		return (0);
	}
	*fd = open(mapfile, O_RDONLY);
	if (*fd == -1)
	{
		ft_printf("Error: Cannot open %s\n", mapfile);
		return (0);
	}
	ft_printf(TY_GREEN"Mapfile %s opened\n"TY_RESET, mapfile);
	return (1);
}

int	validate_directives(int fd, t_params *params)
{
	char	*line;
	char	**tokens;

	ft_printf(TY_YELLOW_B"\nValidating directives\n"TY_RESET);
	while (!completed_params(params))
	{
		line = trim_nl(get_next_line(fd));
		if (!line)
		{
			ft_printf("Error: Missing directive\n");
			return (0);
		}
		tokens = ft_quoted_split(line, " \t", "\"\'");
		if (!process_directive(params, line, tokens))
		{
			ft_split_clean(tokens);
			free(line);
			return (0);
		}
		ft_split_clean(tokens);
		free(line);
	}
	ft_printf(TY_GREEN"All directives found\n"TY_RESET);
	return (1);
}

int	validate_mapdata(int fd, t_params *params)
{
	ft_printf(TY_YELLOW_B"\nImporting map\n"TY_RESET);
	if (!set_map(fd, params))
		return (0);
	ft_printf(TY_LIGHT_GREY_K"Map (raw)"TY_RESET"\n");
	simple_print_map(params->map);
	ft_printf(TY_GREEN_B"Map imported\n"TY_RESET);
	ft_printf(TY_YELLOW_B"\nValidating map\n"TY_RESET);
	if (!validate_map(params))
		return (ft_printf(TY_RED_B"Map is invalid\n"TY_RESET), 0);
	ft_printf(TY_GREEN_B"Map is valid\n"TY_RESET);
	return (1);
}
