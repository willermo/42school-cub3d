/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_printing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:04:45 by doriani           #+#    #+#             */
/*   Updated: 2024/01/15 23:50:03 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_cell2(char c)
{
	if (c == '0')
	{
		write(1, TY_GREEN_K, ft_strlen(TY_GREEN_K));
		write(1, " ", 1);
	}
	else if (ft_strchr("NSEW", c))
	{
		write(1, TY_YELLOW_K, ft_strlen(TY_YELLOW_K));
		write(1, &c, 1);
	}
	else
		write(1, &c, 1);
}

static void	print_cell(char c)
{
	if (c == ' ')
	{
		write(1, TY_DARK_GREY_K, ft_strlen(TY_DARK_GREY_K));
		write(1, " ", 1);
	}
	else if (c == '*')
	{
		write(1, TY_YELLOW_K, ft_strlen(TY_YELLOW_K));
		write(1, "*", 1);
	}
	else if (c == '!')
	{
		write(1, TY_BRIGHT_PURPLE_K, ft_strlen(TY_BRIGHT_PURPLE_K));
		write(1, "!", 1);
	}
	else if (c == '1')
	{
		write(1, TY_RED_K, ft_strlen(TY_RED_K));
		write(1, " ", 1);
	}
	else
		print_cell2(c);
	write(1, TY_RESET, ft_strlen(TY_RESET));
}

void	simple_print_map(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->height && map->map[i])
	{
		write(1, map->map[i++], map->width);
		write(1, "\n", 1);
	}
}

void	print_map(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			print_cell(map->map[i][j++]);
		ft_printf("%d\n", i);
		i++;
	}
}
