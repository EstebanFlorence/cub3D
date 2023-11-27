/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:03:47 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/27 16:10:24 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_north_texture(t_cube *cube)
{
	cube->texture.north.ptr = mlx_xpm_file_to_image(cube.mlx,
			cube->texture.path[0], &cube->texture.north.width,
			&cube->texture.north.height);
	cube->texture.north.data = mlx_get_data_addr(cube->texture.north.ptr,
			&cube->texture.north.bitsxpixel,
			&cube->texture.north.size_line, &cube->texture.north.endian);
}

void	load_south_texture(t_cube *cube)
{
	cube->texture.south.ptr = mlx_xpm_file_to_image(cube.mlx,
			cube->texture.path[1], &cube->texture.south.width,
			&cube->texture.south.height);
	cube->texture.south.data = mlx_get_data_addr(cube->texture.south.ptr,
			&cube->texture.south.bitspixel,
			&cube->texture.south.size_line, &cube->texture.south.endian);
}

void	load_west_texture(t_cube *cube)
{
	cube->texture.west.ptr = mlx_xpm_file_to_image(cube.mlx,
			cube->texture.path[2], &cube->texture.west.width,
			&cube->texture.west.height);
	cube->texture.west.data = mlx_get_data_adrr(cube->texture.west.ptr,
			&cube->texture.west.bitspixel, &cube->texture.west.size_line,
			&cube->texture.west.endian);
}

void	load_east_texture(t_cube *cube)
{
	cube->texture.east.ptr = mlx_xpm_file_to_image(cube.mlx,
			cube->texture.path[3], &cube->texture.east.width,
			&cube->texture.east.height);
	cube->texture.east.data = mlx_get_data_adrr(cube->texture.east.ptr,
			&cube->texture.east.bitspixel, &cube->texture.east.size_line,
			&cube->texture.east.endian);
}

void	ft_convert_image(t_cube *cube)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (cube->texture.cardinal[0] == NORTH)
			load_north_texture(cube);
		else if (cube->texture.cardinal[1] == SOUTH)
			load_south_texture(cube);
		else if (cube->texture.cardinal[2] == WEST)
			load_west_texture(cube);
		else if (cube->texture.cardinal[3] == EAST)
			load_east_texture(cube);
		i++;
	}
}
