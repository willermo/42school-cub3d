/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:09:07 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 04:21:22 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H
# include "mlx.h"
# define LE	0
# define BE	1

typedef struct s_display
{
	void	*mlx;
	void	*win;
}				t_display;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef int				t_rgba;
typedef unsigned char	t_rgb_c;
// defned in mlx_helpers.c
void	init_system(t_display *display, int width, int height, char *title);
int		get_endianness(void);
// defined in mlx_image.c
t_image	*create_image(t_display *display, int width, int height);
t_image	*load_xpm_image(t_display *display, char *path);
void	add_image(t_display *display, t_image *img, t_point p);
void	destroy_image(t_display *display, t_image *img);
void	clear_image(t_display *display, t_image **image);
// defined in mlx_draw.c
void	draw_pixel(t_image *data, t_point coord, int color);
void	draw_line(t_image *image, t_point start, t_point end, int color);
void	draw_square(t_image *data, t_point coord, int color, int size);
void	draw_rectangle(t_image *data, t_point coord, int color, int size[2]);
// defined in mlx_colors.c
t_rgba	create_trgb(t_rgb_c t, t_rgb_c r, t_rgb_c g, t_rgb_c b);
t_rgb_c	get_t(t_rgba trgb);
t_rgb_c	get_r(t_rgba trgb);
t_rgb_c	get_g(t_rgba trgb);
t_rgb_c	get_b(t_rgba trgb);
// defined in mlx_colors2.c
t_rgba	get_random_color(void);
int		get_pixel_color(t_image *image, int x, int y);
int		blend(int src, int dst, double alpha);
#endif
