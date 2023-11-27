/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:03:47 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/27 17:49:06 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_texture(t_cube *cube, int i, t_image *image)
{
	printf("prova ale, path = %s", cube->texture.path[i]);
	image->ptr = mlx_xpm_file_to_image(cube->mlx, "./img/north.xpm" /* cube->texture.path[i] */, &image->width, &image->height);
	if (!image->ptr)
		printf("boh\n");
	image->data = mlx_get_data_addr(image->ptr,
			&image->bitsxpixel,
			&image->size_line, &image->endian);	
}
/* 
void	load_south_texture(t_cube *cube, int i)
{
	cube->texture.south.ptr = mlx_xpm_file_to_image(cube.mlx,
			cube->texture.path[1], &cube->texture.south.width,
			&cube->texture.south.height);
	cube->texture.south.data = mlx_get_data_addr(cube->texture.south.ptr,
			&cube->texture.south.bitspixel,
			&cube->texture.south.size_line, &cube->texture.south.endian);
}

void	load_west_texture(t_cube *cube, int i)
{
	cube->texture.west.ptr = mlx_xpm_file_to_image(cube.mlx,
			cube->texture.path[i], &cube->texture.west.width,
			&cube->texture.west.height);
	cube->texture.west.data = mlx_get_data_adrr(cube->texture.west.ptr,
			&cube->texture.west.bitspixel, &cube->texture.west.size_line,
			&cube->texture.west.endian);
}

void	load_east_texture(t_cube *cube, int i)
{
	cube->texture.east.ptr = mlx_xpm_file_to_image(cube.mlx,
			cube->texture.path[i], &cube->texture.east.width,
			&cube->texture.east.height);
	cube->texture.east.data = mlx_get_data_adrr(cube->texture.east.ptr,
			&cube->texture.east.bitspixel, &cube->texture.east.size_line,
			&cube->texture.east.endian);
} */

void	ft_convert_image(t_cube *cube)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (cube->texture.cardinal[i] == NORTH)
			load_texture(cube, i, &(cube->texture.north));
		else if (cube->texture.cardinal[i] == SOUTH)
			load_texture(cube, i, &cube->texture.south);
		else if (cube->texture.cardinal[i] == WEST)
			load_texture(cube, i, &cube->texture.west);
		else if (cube->texture.cardinal[i] == EAST)
			load_texture(cube, i, &cube->texture.east);
		i++;
	}
}
