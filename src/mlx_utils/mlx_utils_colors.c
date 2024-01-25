/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:21:39 by doriani           #+#    #+#             */
/*   Updated: 2024/01/17 23:21:15 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_utils.h"

t_rgba	create_trgb(t_rgb_c t, t_rgb_c r, t_rgb_c g, t_rgb_c b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_rgb_c	get_t(t_rgba trgb)
{
	return ((trgb >> 24) & 0xFF);
}

t_rgb_c	get_r(t_rgba trgb)
{
	return ((trgb >> 16) & 0xFF);
}

t_rgb_c	get_g(t_rgba trgb)
{
	return ((trgb >> 8) & 0xFF);
}

t_rgb_c	get_b(t_rgba trgb)
{
	return (trgb & 0xFF);
}
