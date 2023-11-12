/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:49:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/12 16:00:41 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/include/ft_printf.h"
# include "libft/include/libft.h"
# include "minilibx-linux/mlx.h"
# include "key.h"

# include <math.h>
# include <stdbool.h>

# define NORTH		2
# define SOUTH		3
# define WEST		4
# define EAST		5
# define FLOOR		6
# define CEILING	7

# define WIN_WIDTH		1000
# define WIN_HEIGHT		1000

# define POS_SHIFT		5

typedef struct s_key
{
	//	bool key;
}	t_key;

typedef struct s_image
{
	void	*ptr;
	char	*data;
	int		bitsxpixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_map
{
	int		cardinal[4];
	char	*tex_path[4];
	int		colors[2][3];

	int		posx;
	int		posy;
	int		x;
	int		y;
	int		**maprix;
	bool	oriented;
	bool	n;
	bool	s;
	bool	e;
	bool	w;
}	t_map;

typedef struct s_ray
{
	float		dir_x;
	float		dir_y;
	int			map_x;
	int			map_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		dist_x;
	float		dist_y;
	float		perp_wall_dist;
	float		wall_x;
	int			x;
	int			color;
	float		step;
	float		tex_pos;
	int			draw_end;
	int			draw_start;
	t_texture	texture;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_ray;

typedef struct s_player
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
}				t_player;

typedef struct s_cube
{
	char	*mapath;
	int		fd;

	void	*mlx;
	void	*win;
	t_image	*img;

	t_map	*map;

}	t_cube;

int		check(int ac);
int		cube_innit(char **av, t_map *map, t_cube *cube);
void	map_innit(t_cube *cube, t_map *map);
void	cube_destroy(t_cube *cube);
void	add_element(char **tok, int *id, int type, t_cube *cube);
void	add_path(char **tok, int i, int type, t_cube *cube);
int		open_path(t_cube *cube);

//	Tools
int		open_path(t_cube *cube);
int		puterr(int n);
void	get_next_close(char *line, t_cube *cube);

//	Mlx
void	mlx_innit(t_cube *cube);
void	mlx_destroy(t_cube *cube);
int		exit_hook(t_cube *cube);
int		key_hook(int key, t_cube *cube);
void	mlx_hooks(t_cube *cube);
void	pixelput(t_image *img, int x, int y, int color);

//	Parsing
void	parser(t_cube *cube);
int		check_next_line(char *line, int *id, t_cube *cube);
int		check_next_map(int start, char *line, t_cube *cube);
int		mapalloc(char *line, t_cube *cube);
int		map_sizecheck(char *line, int *x, int *y, t_cube *cube);
int		line_walls(int i, char *line, t_cube *cube);
int		add_orient(char c, t_cube *cube);
int		linecmp(int i, char *prev_line, char *line);
void	add_map(int start, t_cube *cube);
void	add_element(char **tok, int *id, int type, t_cube *cube);
void	add_path(char **tok, int i, int type, t_cube *cube);
void	add_color(int type, char **tok, t_cube *cube);
void	add_rgb(int type, char **rgb, t_cube *cube);
int		is_map(char *prev_line, char *line, t_cube *cube);
int		is_valid(char c);
int		is_orient(char **tok);
int		is_mapstart(char *line, char **tok, t_cube *cube);
void	free_next_line(char **tok);

void	gotomap(char **line, int start, t_cube *cube);
void	fill_map(char *line, t_cube *cube);
int		coordinate(int i, char *line);


#endif