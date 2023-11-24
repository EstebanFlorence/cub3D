/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:40:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/24 14:19:06 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	extract_pixel_from_image(t_image *img, int point_x, int point_y)
{
	printf("%p", img->data);
	printf("%d", point_x);
	printf("%d", point_y);
	return (*(uint32_t *)(img->data + (point_y * img->size_line) + (point_x
				* img->bitsxpixel / 8)));
}

uint32_t	get_color(t_cube *cube)
{
	t_map		*map;
	t_textures	*textures;

	map = cube->map;
	textures = cube->textures;
	if (!cube->ray->side)
	{
		if (map->orient == WEST)
			return (extract_pixel_from_image(&textures->west, cube->ray->tex_x,
					cube->ray->tex_y));
		else if (map->orient == EAST)
			return (extract_pixel_from_image(&textures->east, cube->ray->tex_x,
					cube->ray->tex_y));
	}
	else
	{
		if (map->orient == NORTH)
			return (extract_pixel_from_image(&textures->north, cube->ray->tex_x,
					cube->ray->tex_y));
		else if (map->orient == SOUTH)
			return (extract_pixel_from_image(&textures->south, cube->ray->tex_x,
					cube->ray->tex_y));
	}
	return (0); // Default color if no texture is found
}

void	next_frame_rendering(t_cube *cube)
{
	ft_raycasting(cube);
	mlx_clear_window(cube->mlx, cube->win);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img->ptr, 0, 0);
}
