/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:49:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/17 19:12:52 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/include/ft_printf.h"
# include "libft/include/libft.h"
# include "minilibx-linux/mlx.h"

# include <math.h>
# include <stdbool.h>

# define NORTH		1
# define SOUTH		2
# define WEST		3
# define EAST		4
# define FLOOR		5
# define CEILING	6

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bitsxpixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_map
{
	int		x;
	int		y;
	int		**maprix;
	bool	n;
	bool	s;
	bool	e;
	bool	w;
}	t_map;

typedef struct s_cube
{
	char	*mapath;
	int		fd;

	int		cardinal[4];
	char	*tex_path[4];
	int		colors[2][3];

	t_map	*map;
	void	*mlx;

}	t_cube;

int		check(int ac);
int		innit(char **av, t_map *map, t_cube *cube);
int		puterr(int n);
void	parser(t_cube *cube);
int		check_next_line(char *line, int *id, t_cube *cube);
void	add_element(char **tok, int *id, int type, t_cube *cube);
void	add_path(char **tok, int i, int type, t_cube *cube);
int		is_mapstart(char *line, t_cube *cube);
int		open_path(t_cube *cube);



#endif