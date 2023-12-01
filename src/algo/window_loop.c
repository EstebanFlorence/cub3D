/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:40:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/12/01 19:40:56 by adi-nata         ###   ########.fr       */
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

	// if (!rc->side)
	// {
	// 	if (box->player.x > rc->map_x)
	// 		return (extract_pixel_from_image(&box->textures.west,
	// 				rc->tex_x, rc->tex_y));
	// 	return (extract_pixel_from_image(&box->textures.east,
	// 			rc->tex_x, rc->tex_y));
	// }
	// if (box->player.y > rc->map_y)
	// 	return (extract_pixel_from_image(&box->textures.north,
	// 			rc->tex_x, rc->tex_y));
	// return (extract_pixel_from_image(&box->textures.south,
	// 		rc->tex_x, rc->tex_y));



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

// void	next_frame_rendering(t_cube *cube)
// {
// 	// if (cube->img->ptr)
// 	// 	mlx_destroy_image(cube->mlx, cube->img->ptr);
// 	// mlx_destroy_(cube->mlx, cube->win);
// }

int	window_loop(t_cube *cube)
{
	// next_frame_rendering(cube);
	if (cube->img->ptr)
		mlx_destroy_image(cube->mlx, cube->img->ptr);
	ft_raycasting(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img->ptr, 0, 0);
	//cube->img.data = NULL;
	return (0);
}
