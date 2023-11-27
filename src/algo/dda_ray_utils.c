/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:58:00 by  gcavanna         #+#    #+#             */
/*   Updated: 2023/11/27 18:02:01 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_wall_height(t_ray *ray)
{
	if (!ray->side)
		ray->perp_wall_dist = ray->side_dist.x
			- ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y
			- ray->delta_dist.y;
	/* if (ray->perp_wall_dist <= 0.00001)
		ray->perp_wall_dist = 0.00001; */
	printf("lh = %d", ray->line_height);
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	ft_texture_coord(t_cube *cube, t_ray *ray)
{
	if (!ray->side)
	{
		ray->wall_x = cube->player.pos.y + ray->perp_wall_dist
			* ray->dir.y;
	}
	else
	{
		ray->wall_x = cube->player.pos.x + ray->perp_wall_dist
			* ray->dir.x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if ((!ray->side && ray->dir.x > 0) || (ray->side
			&& ray->dir.y < 0))
	{
		ray->tex.x = TEXTURE_WIDTH - ray->tex.x - 1;
	}
	ray->tex.x = abs((int)ray->tex.x);
	ray->step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	ray->tex_pos = (ray->draw_start - (WIN_HEIGHT / 2)
			+ ray->line_height / 2) * ray->step;
}

t_image	*new_img(void *mlx_ptr)
{
	t_image	*new_img;

	new_img = (t_image *)malloc(sizeof(t_image));
	if (new_img)
	{
		new_img->ptr = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		new_img->data = mlx_get_data_addr(new_img->ptr, &new_img->bitsxpixel,
				&new_img->size_line, &new_img->endian);
	}
	return (new_img);
}

void	put_pixel_in_image(t_image *img, int x, int y, uint32_t color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bitsxpixel / 8));
	*(uint32_t *)dst = color;
}

void	draw_wall(int x, t_cube *cube, t_ray *ray)
{
	int	y;

	y = -1;
	/* printf("ale draw start = %d\n", ray->draw_start);
	if (ray->draw_start >= WIN_HEIGHT)
		return ; */
	while (++y < ray->draw_start)
	{
		put_pixel_in_image(cube->img, x, y, cube->texture.skyground[0]);
	}
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex.y = (int)ray->tex_pos & (TEXTURE_HEIGHT - 1);
		ray->tex_pos += ray->step;
		printf("%d %d\n", ray->draw_end, ray->draw_start);
		put_pixel_in_image(cube->img, x, y, get_color(cube, ray));
		y += 1;
	}
	printf("caio\n");
	while (y < WIN_HEIGHT / 2)
	{
		put_pixel_in_image(cube->img, x, y, cube->texture.skyground[1]);
		y += 1;
	}
}
