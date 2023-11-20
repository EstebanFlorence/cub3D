/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:40:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/20 15:04:57 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	extract_pixel_from_image(t_cube *cube, t_image *img, int point_x,
		int point_y)
{
	return (*(uint32_t *)(cube->img->data + (point_y * cube->img->size_line)
			+ (point_x * cube->img->bitsxpixel / 8)));
}

uint32_t	get_color(t_cube *cube, t_ray *ray)
{
	if (!ray->side)
	{
		if (cube->player->pos_x > ray->map_x)
			return (extract_pixel_from_image(cube, cube->map->cardinal[4],
												ray->tex_x,
												ray->tex_y));
		return (extract_pixel_from_image(cube, cube->map->cardinal[5],
											ray->tex_x,
											ray->tex_y));
	}
	if (cube->player->pos_y > ray->map_y)
		return (extract_pixel_from_image(cube, cube->map->cardinal[2],
											ray->tex_x,
											ray->tex_y));
	return (extract_pixel_from_image(cube, cube->map->cardinal[3],
										ray->tex_x,
										ray->tex_y));
}

void	next_frame_rendering(t_cube *cube)
{
	ft_raycasting(cube);
	mlx_clear_window(cube->mlx, cube->win);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img->ptr, 0, 0);
}
