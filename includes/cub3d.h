/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:26:05 by doriani           #+#    #+#             */
/*   Updated: 2024/01/24 05:21:29 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/Xlib.h>
# include "libft.h"
# include "mlx.h"
# include "mlx_utils.h"
# include "cub3d_mlx_defs.h"
# include "typography.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>

# define MAP_CHARS "012NSEW dD"
# define FOV_W 66
# define FOV_H 33
# define VERBOSE 1
# define BITS 8
# define CELLSIZE 16
# define PACE 2
# define ROTATION_STEP_DEGREE 2
# define MAX_HP_POINTS 100
# define MAX_MANA_POINTS 100
# define PLAYER_START_HP_POINTS 80
# define PLAYER_START_MANA_POINTS 60
# define DOOR_TEXTURE "./res/textures/door_texture.xpm"
# define PISTOL_TEXTURE_0 "./res/sprites/pistol0.xpm"
# define PISTOL_TEXTURE_1 "./res/sprites/pistol1.xpm"
# define PISTOL_TEXTURE_2 "./res/sprites/pistol2.xpm"
# define PISTOL_TEXTURE_3 "./res/sprites/pistol3.xpm"
# define PISTOL_TEXTURE_4 "./res/sprites/pistol4.xpm"

typedef enum e_rotation
{
	LEFT,
	RIGHT
}	t_rotation;

typedef enum e_component
{
	SCREEN,
	HEADER,
	MINIMAP,
	SCENE,
	ALL
}	t_component;

typedef enum e_gamescene
{
	MAIN,
	EXPLORE2D,
	EXPLORE3D,
	GAME2D,
	GAME3D
}	t_gamescene;

typedef struct s_playerstats
{
	int	health;
	int	mana;
}	t_playerstats;

typedef struct s_raycast
{
	double	wall_dis;
	int		lineh;
	int		drowstart;
	int		drowend;
	int		color;
	double	fov_h;
	int		orientation;
	double	w_per;
	int		door;
}	t_raycast;

typedef struct s_dda
{
	double	sidex;
	double	sidey;
	double	ini_pos_x;
	double	ini_pos_y;
	int		tmpdir;
	double	tmpx;
	double	tmpy;
	double	tanray;
}	t_dda;

typedef struct s_texture
{
	int	**array;
	int	columns;
	int	rows;
	int	colors;
	int	chars_per_pixel;
}	t_texture;

typedef struct s_player
{
	int				x;
	int				y;
	double			dx;
	double			dy;
	double			cart_x;
	double			cart_y;
	int				orientation;
	t_playerstats	stats;
}	t_player;

typedef struct s_map
{
	char		**map;
	char		**inverted_map;
	size_t		width;
	size_t		height;
	int			is_valid;
	int			player_found;
	int			player_startpos[2];
	char		player_orientation;
	t_player	*player;
}	t_map;

typedef struct s_params
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f[3];
	int			c[3];
	t_map		*map;
	t_dda		dda;
	t_raycast	raycast;
}	t_params;

typedef struct s_cub3d
{
	t_display	display;
	t_image		*image;
	t_image		*header;
	t_image		*minimap;
	t_image		*screen;
	t_image		*refresh;
	t_image		*pistol;
	t_params	*params;
	t_map		*map;
	t_player	*player;
	t_texture	texture_north;
	t_texture	texture_south;
	t_texture	texture_east;
	t_texture	texture_west;
	t_texture	texture_sprite[5];
	t_texture	texture_door;
	t_dda		dda;
	t_raycast	raycast;
	t_gamescene	gamescene;
}	t_cub3d;

// ROUTINE SECTION
// cub3d_helpers.c
void		print_player(t_player *player, char *title);
void		print_session_summary(t_params *params);
// cub3d_routine.c
void		init_params(t_params *params);
int			parse_mapfile(char *mapfile, t_params *params);
void		start_cub3d(char *mapfile, t_params *params);
void		clean_params(t_params *params);

// VALIDATION SECTION
// validator.c
int			validate_mapfile_name(int *fd, char *mapfile);
int			validate_directives(int fd, t_params *params);
int			validate_mapdata(int fd, t_params *params);
// validator_helpers.c
int			completed_params(t_params *params);
int			is_empty_line(char *line);
char		*trim_nl(char *line);
t_sl_list	*maplist_error(t_sl_list **maplist, char **line, char *error);
// validator_directives.c
int			process_directive(t_params *params, char *line, char **tokens);
// validator_directives2.c
char		**get_texture_path(t_params *params, char *directive);
int			*get_rgb_color(t_params *params, char *directive);
char		*get_what(char *directive);
int			add_texture(char **path, char *token, const char *what);
int			add_rgb_color(int *rgb_color, char *token, const char *what);
// validator_map_parsing.c
t_sl_list	*get_maplist(int fd, t_params *params);
int			set_map(int fd, t_params *p);
// validator_map_printing.c
void		simple_print_map(t_map *map);
void		print_map(t_map *map);
// validator_map_validation.c
int			validate_map(t_params *params);
// validator_map_validation_helpers.c
int			test_cell(t_map *map, int i, int j);
// validator_map_validation_utils.c
int			clean_mapdata(t_map *mapdata);
char		**copy_map(t_params *params);
t_map		*clone_mapdata(t_params *params);
void		sync_mapdata_metadata(t_map *src, t_map *dest);

// MLX SECTION
// defined in mlx_common.c
void		init_cub3d(t_cub3d *cub3d, t_params *params);
void		init_hooks(t_cub3d *cub3d);
void		destroy_mlx(t_cub3d *cub3d);
// defined in mlx_linux_hooks.c
int			keypress(int ks, t_cub3d *f);
int			x_click(t_display *display);
int			mouse_hook(int x, int y, t_cub3d *f);
// defined in cub3d_actions_move.c
void		move(t_cub3d *cub3d, double orientation, char *move_name);
void		rotate(t_cub3d *cub3d, t_rotation rotation, char *move_name);
void		activate_door(t_cub3d *cub3d, int orientation);
// defined in mlx_render.c
void		refresh(t_cub3d *cub3d, t_component component, t_point coords);
void		render_gamescreen(t_cub3d *cub3d);
// defined in mlx_render_draws.c
void		draw_background(t_image *img, t_rgba color, int random, int prog);
void		draw_stats(t_cub3d *cub3d);
// defined in mlx_render_minimap.c
void		draw_minimap(t_cub3d *cub3d, t_image *img, int size[2]);
// defined in mlx_render_pistol.c
void		render_pistol(t_cub3d *cub3d, int frame);
void		draw_pistol(t_cub3d *cub3d, t_image *img, int frame);
void		shoot_pistol(t_cub3d *cub3d);
// defined in mlx_render_3dscene.c
void		draw_3dscene(t_cub3d *cub3d, t_image *img, int size[2]);

// RAYCASTING SECTION
//  defined in dda.c
void		dda_90(t_cub3d *cub3d, int tan);
void		dda_init(t_cub3d *cub3d, t_image *img);
// defined in dda_utils.c
void		dda_next_int_defdinedx(t_params *params, int tan);
void		dda_next_int_defdixnedy(t_params *params, int tan);
int			right_data(t_params *params, double tmpy, double tmpx, \
				t_cub3d *cub3d);
int			dda_in_map(t_params *params, int tan);
// defined in dda_norminette.c
double		dda_distance(double x, double y, double x1, double y1);
void		dda_line_long(t_cub3d *cub3d);
// defined in raycasting.c
void		raycasting(t_cub3d *cub3d, t_image *img, int x, double tanori);
// defined in set_up_texture.c
void		set_up_texture(t_cub3d *cub3d);
// defined in set_up_texture2.c
char		*text_general_val(int fd);
void		init_gen_val(t_texture *texture, int fd);
char		*ret_line(int fd);
int			hex_to_rgb(char *line);
int			gray_to_rgb(char *line);
// defined in set_up_texture3.c
int			conv_int(char *line);
char		*fill_info(int fd, int *pixel_color, int i, int char_set_size);
int			*charset_to_number(t_texture *texture, char **charset, \
	int *pixel_color, char *line);
void		close_function(char **charset, int *pixel_color, int fd, \
	int charset_size);
void		parser_xpm(t_texture *texture, char *path);

#endif
