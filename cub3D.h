/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:49:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/04 16:53:58 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "key.h"
# include "libft/include/ft_printf.h"
# include "libft/include/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdint.h>

# define NORTH 2
# define SOUTH 3
# define WEST 4
# define EAST 5
# define FLOOR 6
# define CEILING 7

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define MAP_WIDTH 150
# define MAP_HEIGHT 200

# define TILES_X 15
# define TILES_Y 20

# define MOV_SPEED 0.05f
# define ROT_SPEED 0.01
# define MARGIN	0.2f

typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_ray
{
	t_coord		dir;
	t_coord		map;
	t_coord		delta_dist;
	t_coord		side_dist;
	double		perp_wall_dist;
	double		wall_x;
	int			line_height;
	int			x;
	int			color;
	double		step;
	double		tex_pos;
	int			draw_end;
	int			draw_start;
	int			step_x;
	int			step_y;
	bool		hit;
	int			side;
	t_coord		tex;
	double		camera_x;
}				t_ray;

typedef struct s_cam
{
	t_coord		pos;
	t_coord		dir;
	t_coord		plane;
	t_coord		ray_dir;
}				t_cam;

typedef struct s_image
{
	void		*ptr;
	char		*data;
	int			width;
	int			height;
	int			bitsxpixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_tex
{
	int			cardinal[4];
	char		*path[4];
	int			skyground[2];

	t_image		north;
	t_image		south;
	t_image		east;
	t_image		west;

}				t_tex;

typedef struct s_index
{
	int	x;
	int	y;
	int	i;
}		t_index;

typedef struct s_map
{
	t_coord		size;
	int			orient;
	int			**maprix;

}				t_map;

typedef struct s_cube
{
	char		*mapath;
	int			fd;

	t_map		map;
	t_tex		texture;
	t_cam		player;
	t_image		*img;

	void		*mlx;
	void		*win;
}				t_cube;

int				check(int ac);
int				cube_innit(char **av, t_cube *cube);
void			map_innit(t_cube *cube);
void			texture_innit(t_cube *cube);
void			cube_destroy(t_cube *cube);
void			add_element(char **tok, int *id, int type, t_cube *cube);
int				open_path(t_cube *cube);
void			start(t_cube *cube);

//				Tools
int				open_path(t_cube *cube);
int				check_path(char **tok);
int				puterr(int n);
void			get_next_close(char *line, t_cube *cube);

//				Mlx
void			mlx_innit(t_cube *cube);
void			mlx_destroy(t_cube *cube);
void			mlx_hooks(t_cube *cube);
void			pixelput(t_image *img, int x, int y, int color);
int				exit_hook(t_cube *cube);
int				key_hook(int key, t_cube *cube);

//				Movements
void			move_left(t_cube *cube);
void			move_right(t_cube *cube);
void			move_up(t_cube *cube);
void			move_down(t_cube *cube);
void			rotate_sx(t_cube *cube);
void			rotate_dx(t_cube *cube);

//				Parsing
void			parser(t_cube *cube);
void			free_next_line(char **tok);
void			gotomap(char **line, int start, t_cube *cube);
void			add_element(char **tok, int *id, int type, t_cube *cube);
void			add_path(char *path, int i, int type, t_cube *cube);
void			add_color(int type, char **tok, t_cube *cube);
void			add_rgb(int type, char **rgb, t_cube *cube);
void			map_index(t_index *index);
int				add_map(int start, t_cube *cube);
int				fill_map(char *line, t_cube *cube);
int				check_next_line(char *line, int *id, t_cube *cube);
int				check_next_map(int start, char *line, t_cube *cube);
int				mapalloc(char *line, t_cube *cube);
int				map_sizecheck(char *line, int *x, int *y, t_cube *cube);
int				line_walls(int i, char *line, t_cube *cube);
int				add_orient(char c, t_cube *cube);
int				linecmp(int i, char *prev_line, char *line);
int				is_map(char *prev_line, char *line, t_cube *cube);
int				is_valid(char c);
int				is_orient(char **tok);
int				is_mapstart(char *line, char **tok, t_cube *cube);
int				coordinate(char c);

//raycasting
void			ft_wall_height(t_ray *ray);
void			ft_texture_coord(t_cube *cube, t_ray *ray);
t_image			*new_img(void *mlx_ptr);
void			put_pixel_in_image(t_image *img, int x, int y, uint32_t color);
void			draw_wall(int x, t_cube *cube, t_ray *ray);

void			ft_init_ray(int x, t_cube *cube, t_ray *ray);
unsigned int	color_convert(int r, int g, int b);
void			ft_init_side_distance(t_cube *cube, t_ray *ray);
void			ft_wall_collision_detection(t_cube *cube, t_ray *ray);
void			ft_raycasting(t_cube *cube);
void			next_frame_rendering(t_cube *cube);
int				window_loop(t_cube *cube);
int				extract_pixel_from_image(t_image *img,
					int point_x, int point_y);
uint32_t		get_color(t_cube *cube, t_ray *ray);

//player
void			set_plr_pov(t_cam *player, int dir);
void			ft_get_cam_pos(t_cube *cube);
void			set_plr_pov_north(t_cam *player);
void			set_plr_pov_south(t_cam *player);
void			set_plr_pov_west(t_cam *player);
void			set_plr_pov_east(t_cam *player);

//xpm
void			load_north_texture(t_cube *cube);
void			load_south_texture(t_cube *cube);
void			load_west_texture(t_cube *cube);
void			load_east_texture(t_cube *cube);
void			ft_convert_image(t_cube *cube);

#endif