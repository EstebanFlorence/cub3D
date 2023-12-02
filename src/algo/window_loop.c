/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:40:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/12/02 19:14:09 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	extract_pixel_from_image(t_image *img, int point_x, int point_y)
{
	return (*(uint32_t *)(img->data + (point_y * img->size_line) + (point_x
			* img->bitsxpixel / 8)));
}

uint32_t	get_color(t_cube *cube, t_ray *ray)
{
	if (!ray->side)
	{
		if (cube->player.pos.x > ray->map.x)
			return (extract_pixel_from_image(&cube->texture.west, ray->tex.x,
					ray->tex.y));
		return (extract_pixel_from_image(&cube->texture.east, ray->tex.x,
				ray->tex.y));
	}
	else
	{
		if (cube->player.pos.y > ray->map.y)
			return (extract_pixel_from_image(&cube->texture.north, ray->tex.x,
					ray->tex.y));
		return (extract_pixel_from_image(&cube->texture.south, ray->tex.x,
				ray->tex.y));
	}
	return (0);
}

int	window_loop(t_cube *cube)
{
	if (cube->img->ptr)
		mlx_destroy_image(cube->mlx, cube->img->ptr);
	ft_raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img->ptr, 0, 0);
	return (0);
}
