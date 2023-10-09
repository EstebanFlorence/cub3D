/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:49:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/09 18:40:07 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/include/ft_printf.h"
# include "libft/include/libft.h"
# include "minilibx-linux/mlx.h"

# include <math.h>

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

typedef struct s_cube
{
	char	*mapath;
	int		fd;

	int		cardinal[4];
	char	*paths[4];
	int		skyground[2];
	int		colors[2][3];

	void	*mlx;

}	t_cube;

#endif