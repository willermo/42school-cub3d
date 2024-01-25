/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:26:21 by doriani           #+#    #+#             */
/*   Updated: 2024/01/16 13:20:29 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	print_usage_and_exit(void)
{
	ft_printf("Usage: cub3d <mapfile>\n");
	exit(1);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc != 2)
		print_usage_and_exit();
	init_params(&params);
	if (parse_mapfile(argv[1], &params))
		start_cub3d(argv[1], &params);
	clean_params(&params);
	ft_printf(TY_BLUE_B"\nExiting cub3d\n"TY_RESET);
	return (0);
}
