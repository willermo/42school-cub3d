/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_texture2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 05:08:43 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 05:12:55 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*text_general_val(int fd)
{
	char	c[2];
	char	*str;
	char	*tmp;
	int		i;

	c[0] = '\0';
	c[1] = '\0';
	i = -1;
	while (++i < 3)
	{
		while (c[0] != '\n' && (read(fd, c, 1)) > 0)
			c[1] = '\0';
		read(fd, c, 1);
	}
	str = ft_strdup(c);
	while (c[0] != '\n' && (read(fd, c, 1)) > 0)
	{
		c[1] = '\0';
		tmp = ft_strjoin(str, c);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
	}
	return (str);
}

void	init_gen_val(t_texture *texture, int fd)
{
	char		*str;
	char		**gen_val;

	str = text_general_val(fd);
	gen_val = ft_split(str, " ");
	free(str);
	texture->columns = ft_atoi(&gen_val[0][1]);
	texture->rows = ft_atoi(gen_val[1]);
	texture->colors = ft_atoi(gen_val[2]);
	texture->chars_per_pixel = ft_atoi(gen_val[3]);
	ft_split_clean(gen_val);
}

char	*ret_line(int fd)
{
	char	c[2];
	char	*str;
	char	*tmp;

	tmp = NULL;
	str = NULL;
	read(fd, c, 1);
	c[1] = '\0';
	str = ft_strdup(c);
	while (!(ft_strchr(c, '\n')) && (read(fd, c, 1)) > 0)
	{
		c[1] = '\0';
		tmp = ft_strjoin(str, c);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
	}
	return (str);
}

int	hex_to_rgb(char *line)
{
	int			ret;
	int			i;

	i = -1;
	ret = 0;
	line ++;
	while (++i < 2)
	{
		if (*line >= '0' && *line <= '9')
			ret += ((*line) - 48) * pow(16, i);
		if (*line >= 'A' && *line <= 'F')
			ret += (*line) - 55 * pow(16, i);
		line --;
	}
	return (ret);
}

int	gray_to_rgb(char *line)
{
	char	gray[4];

	gray[0] = *line;
	gray[1] = *(line + 1);
	if (*(line + 2) == '0')
	{
		gray[2] = *(line + 2);
		gray[3] = '\0';
	}
	else
		gray[2] = '\0';
	return ((ft_atoi(gray) * 255) / 100);
}
