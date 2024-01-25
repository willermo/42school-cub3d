/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_texture3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:08:54 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 05:12:49 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	conv_int(char *line)
{
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	if (*line == '#')
	{
		line ++;
		r = hex_to_rgb(line);
		g = hex_to_rgb(line + 2);
		b = hex_to_rgb(line + 4);
	}
	else if (ft_strncmp(line, "gray", 4) == 0)
	{
		r = gray_to_rgb(line + 4);
		g = r;
		b = g;
	}
	else if (ft_strncmp(line, "None", 4) == 0)
		return (-1);
	return ((r << 16L) + (g << 8L) + b);
}

char	*fill_info(int fd, int *pixel_color, int i, int char_set_size)
{
	char	*line;
	char	*char_set;
	int		cont;

	cont = -1;
	line = NULL;
	line = ret_line(fd);
	char_set = ft_calloc(char_set_size + 1, 1);
	while (++cont < char_set_size)
		char_set[cont] = line[cont + 1];
	char_set[cont] = '\0';
	pixel_color[i] = conv_int(line + 4 + char_set_size);
	free(line);
	return (char_set);
}

int	*charset_to_number(t_texture *texture, char **charset, \
	int *pixel_color, char *line)
{
	int	j;
	int	charset_i;
	int	*ret;

	j = -1;
	charset_i = -1;
	ret = ft_calloc(texture->columns / texture->chars_per_pixel, sizeof(int));
	while (++j < texture->columns / texture->chars_per_pixel)
	{
		while (++charset_i < texture->colors)
			if (!ft_strncmp(line, charset[charset_i], texture->chars_per_pixel))
				break ;
		ret[j] = pixel_color[charset_i];
		charset_i = -1;
		line = line + texture->chars_per_pixel;
	}
	return (ret);
}

void	close_function(char **charset, int *pixel_color, int fd, \
	int charset_size)
{
	int	i;

	i = -1;
	close(fd);
	while (++i < charset_size)
		free(charset[i]);
	free(charset);
	free(pixel_color);
}

void	parser_xpm(t_texture *texture, char *path)
{
	int		fd;
	char	**charset;
	int		*pixel_color;
	int		i;
	char	*line;

	i = -1;
	fd = open(path, O_RDONLY);
	init_gen_val(texture, fd);
	pixel_color = ft_calloc(texture->colors, sizeof(int));
	charset = ft_calloc(texture->colors, sizeof(char *));
	while (++i < texture->colors)
		charset[i] = fill_info(fd, pixel_color, i, texture->chars_per_pixel);
	free(ret_line(fd));
	i = -1;
	texture->array = ft_calloc(texture->rows, sizeof(int *));
	while (++i < texture->rows)
	{
		line = ret_line(fd);
		texture->array[i] = charset_to_number(texture, charset, pixel_color, \
			(line + 1));
		free(line);
	}
	close_function(charset, pixel_color, fd, texture->colors);
}
