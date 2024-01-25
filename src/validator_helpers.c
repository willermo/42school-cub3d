/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:38:14 by doriani           #+#    #+#             */
/*   Updated: 2024/01/14 14:35:07 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	completed_params(t_params *params)
{
	return (params->no_path && params->so_path \
		&& params->ea_path && params->we_path \
		&& params->f[0] >= 0 && params->c[0] >= 0);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*trim_nl(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

t_sl_list	*maplist_error(t_sl_list **maplist, char **line, char *error)
{
	ft_printf("Error: %s\n", error);
	free(*line);
	sl_destroy_list(maplist);
	return (NULL);
}
