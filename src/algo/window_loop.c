/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:40:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/24 23:06:51 by adi-nata         ###   ########.fr       */
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

uint32_t	get_color(t_cube *cube, t_ray *ray)
{
	t_map		*map;
	t_tex	*textures;

	map = cube->map;
	textures = cube->texture;
	if (!ray->side)
	{
		if (map->orient == WEST)
			return (extract_pixel_from_image(&textures->west, ray->tex.x,
					ray->tex.y));
		else if (map->orient == EAST)
			return (extract_pixel_from_image(&textures->east, ray->tex.x,
					ray->tex.y));
	}
	else
	{
		if (map->orient == NORTH)
			return (extract_pixel_from_image(&textures->north, ray->tex.x,
					ray->tex.y));
		else if (map->orient == SOUTH)
			return (extract_pixel_from_image(&textures->south, ray->tex.x,
					ray->tex.y));
	}
	return (0); // Default color if no texture is found
}

void	next_frame_rendering(t_cube *cube)
{
	ft_raycasting(cube);
	mlx_clear_window(cube->mlx, cube->win);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img->ptr, 0, 0);
}

int	window_loop(t_cube *cube)
{
	next_frame_rendering(cube);
	mlx_destroy_image(cube->mlx, cube->img->ptr);
	cube->img->data = NULL;
	return (0);
}