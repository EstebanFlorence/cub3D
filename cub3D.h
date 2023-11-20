/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:49:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/20 14:52:14 by gcavanna         ###   ########.fr       */
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

# define NUM_TILES_X 15
# define NUM_TILES_Y 20

# define TILE_SIZE_X (MAP_WIDTH / NUM_TILES_X)
# define TILE_SIZE_Y (MAP_HEIGHT / NUM_TILES_Y)

# define POS_SHIFT 5

/* typedef struct	s_var
{
	double	pos_x;
	double	pos_y;

	double	dir_x;
	double	dir_y;

	double	raydir_x;
	double	raydir_y;

	double	firstdist_x;
	double	firstdist_y;

	double	deltadist_x;
	double	deltadist_y;

	double	plane_x;
	double	plane_y;

	double	camera_x;

	double	step_x;
	double	step_y;

	double	map_x;	// = pos_x
	double	map_y;	// = pos_y

	double	perpwalldist;



}				t_var;

typedef struct	s_ray
{

}				t_ray;

typedef struct	s_play
{

}				t_play;
 */
typedef struct s_key
{
	//	bool key;
}				t_key;

typedef struct s_image
{
	void		*ptr;
	char		*data;
	int			bitsxpixel;
	int			size_line;
	int			endian;
}				t_image;

typedef struct s_texturer
{
	int			sky[3];
	int			floor[3];
}				t_textures;

typedef struct s_map
{
	int			cardinal[4];
	char		*tex_path[4];
	int			colors[2][3];

	int			x;
	int			y;
	int			orient;
	int			**maprix;
	bool		oriented;
	bool		n;
	bool		s;
	bool		e;
	bool		w;
}				t_map;

typedef struct s_ray
{
	float		dir_x;
	float		dir_y;
	int			map_x;
	int			map_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	float		perp_wall_dist;
	float		wall_x;
	int			line_height;
	int			x;
	int			color;
	float		step;
	float		tex_pos;
	int			draw_end;
	int			draw_start;
	//t_texture	texture;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			tex_x;
	int			tex_y;

	double		camera_x;
}				t_ray;

typedef struct s_play
{
	float		pos_x;
	float		pos_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		move_speed;
	float		rot_speed;
	float		ray_dir_x;
	float		ray_dir_y;
}				t_play;

typedef struct s_cube
{
	char		*mapath;
	int			fd;

	void		*mlx;
	void		*win;
	t_textures	*textures;
	t_play		*player;
	t_image		*img;
	t_ray		*ray;
	t_map		*map;

}				t_cube;

int				check(int ac);
int				cube_innit(char **av, t_cube *cube);
void			map_innit(t_cube *cube, t_map *map);
void			rayplay_innit(t_cube *cube, t_ray *ray, t_play *player);
void			cube_destroy(t_cube *cube);
void			add_element(char **tok, int *id, int type, t_cube *cube);
void			add_path(char **tok, int i, int type, t_cube *cube);
int				open_path(t_cube *cube);

//	Tools
int				open_path(t_cube *cube);
int				puterr(int n);
void			get_next_close(char *line, t_cube *cube);

//	Mlx
void			mlx_innit(t_cube *cube);
void			mlx_destroy(t_cube *cube);
int				exit_hook(t_cube *cube);
int				key_hook(int key, t_cube *cube);
void			mlx_hooks(t_cube *cube);
void			pixelput(t_image *img, int x, int y, int color);

//	Try
void			starter(t_cube *cube);
void			setdir(t_cube *cube);

//	Parsing
void			parser(t_cube *cube);
int				check_next_line(char *line, int *id, t_cube *cube);
int				check_next_map(int start, char *line, t_cube *cube);
int				mapalloc(char *line, t_cube *cube);
int				map_sizecheck(char *line, int *x, int *y, t_cube *cube);
int				line_walls(int i, char *line, t_cube *cube);
int				add_orient(char c, t_cube *cube);
int				linecmp(int i, char *prev_line, char *line);
void			add_map(int start, t_cube *cube);
void			add_element(char **tok, int *id, int type, t_cube *cube);
void			add_path(char **tok, int i, int type, t_cube *cube);
void			add_color(int type, char **tok, t_cube *cube);
void			add_rgb(int type, char **rgb, t_cube *cube);
int				is_map(char *prev_line, char *line, t_cube *cube);
int				is_valid(char c);
int				is_orient(char **tok);
int				is_mapstart(char *line, char **tok, t_cube *cube);
void			free_next_line(char **tok);

void			gotomap(char **line, int start, t_cube *cube);
void			fill_map(char *line, t_cube *cube);
int				coordinate(int i, char *line);

//raycasting
//int		ft_wall_height(t_ray *ray, int win_height);
void			ft_wall_height(t_cube *cube);
void			ft_texture_coord(t_ray *ray, t_cube *cube);
//void		ft_render(t_ray *ray, t_cube *cube, int y);
t_image			*new_img(void *mlx_ptr);
void			put_pixel_in_image(t_image *img, int x, int y, uint32_t color);
//void			ft_draw_wall(t_ray *ray, t_cube *cube);
void			draw_wall(t_cube *cube, t_ray *ray, int x);

//t_ray	ft_init_ray(float camera_x, t_cube *cube);
void			ft_init_ray(int x, t_cube *cube);
//t_ray	ft_init_side_distance(t_cube *cube);
unsigned int	color_convert(int r, int g, int b);
void			ft_init_side_distance(t_cube *cube);
void			ft_wall_collision_detection(t_cube *cube);
void			ft_raycasting(t_cube *cube);
void			next_frame_rendering(t_cube *cube);
int				extract_pixel_from_image(t_cube *cube, t_image *img,
					int point_x, int point_y);
uint32_t		get_color(t_cube *cube, t_ray *ray);

//player
void			set_plr_pov(t_play *player, char dir);
void			ft_get_play_pos(t_cube *cube);

#endif