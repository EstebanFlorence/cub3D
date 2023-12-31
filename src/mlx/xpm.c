/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:03:47 by gcavanna          #+#    #+#             */
/*   Updated: 2023/12/02 19:42:59 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_texture(t_cube *cube, int i, t_image *image)
{
	image->ptr = mlx_xpm_file_to_image(cube->mlx, cube->texture.path[i],
			&image->width, &image->height);
	if (!image->ptr)
		ft_printf("Ecco immagine inesistente");
	image->data = mlx_get_data_addr(image->ptr,
			&image->bitsxpixel,
			&image->size_line,
			&image->endian);
}

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
