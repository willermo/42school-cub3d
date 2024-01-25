/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:35:07 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 05:07:07 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_empty_lines(int fd)
{
	char	*line;

	line = trim_nl(get_next_line(fd));
	while (line && is_empty_line(line))
	{
		free(line);
		line = trim_nl(get_next_line(fd));
	}
	return (line);
}

static int	remaining_lines_are_empty(int fd)
{
	char	*line;

	line = trim_nl(get_next_line(fd));
	while (line)
	{
		if (!is_empty_line(line))
		{
			free(line);
			return (0);
		}
		free(line);
		line = trim_nl(get_next_line(fd));
	}
	return (1);
}

static int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(MAP_CHARS, line[i++]))
			continue ;
		return (0);
	}
	return (1);
}

t_sl_list	*get_maplist(int fd, t_params *params)
{
	t_sl_list	*new;
	char		*line;

	new = NULL;
	line = skip_empty_lines(fd);
	while (line)
	{
		if (is_empty_line(line) && !remaining_lines_are_empty(fd))
			return (maplist_error(&new, &line, "Unexpected data after map"));
		if (!is_valid_map_line(line))
			return (maplist_error(&new, &line, "Invalid map line"));
		if (new)
			sl_insert_end(&new, ft_strdup(line));
		else
			new = sl_create_node(ft_strdup(line));
		if (ft_strlen(line) > params->map->width)
			params->map->width = ft_strlen(line);
		params->map->height++;
		free(line);
		line = trim_nl(get_next_line(fd));
	}
	return (new);
}

int	set_map(int fd, t_params *p)
{
	unsigned int	i;
	unsigned int	j;
	t_sl_list		*maplist;
	t_sl_list		*runner;

	maplist = get_maplist(fd, p);
	if (!maplist)
		return (0);
	runner = maplist;
	p->map->map = (char **) malloc(sizeof(char *) * p->map->height);
	p->map->inverted_map = (char **) malloc(sizeof(char *) * p->map->height);
	i = 0;
	while (i < p->map->height)
	{
		j = ft_strlen((char *) sl_get_node_data(runner));
		p->map->map[i] = (char *) malloc(sizeof(char) * p->map->width);
		ft_memcpy(p->map->map[i], (char *) sl_get_node_data(runner), j);
		while (j < p->map->width)
			p->map->map[i][j++] = ' ';
		p->map->inverted_map[p->map->height - i - 1] = p->map->map[i];
		runner = runner->next;
		i++;
	}
	return (sl_destroy_list(&maplist), 1);
}
