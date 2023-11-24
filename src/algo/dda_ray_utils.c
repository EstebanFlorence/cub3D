/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:58:00 by  gcavanna         #+#    #+#             */
/*   Updated: 2023/11/24 23:06:51 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* int	ft_wall_height(t_ray *ray, int win_height)
{
	int	wall_height;

	wall_height = (int)(win_height / ray->perp_wall_dist);
	return (wall_height);
}

void	ft_texture_coord(t_ray *ray, t_cube *cube)
{
	int	tex_x;
	int	tex_y;

	if (ray->side == 0)
		ray->wall_x = cube->player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = cube->player->pos.y + ray->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	tex_x = (int)(ray->wall_x * (double)(cube->img->size_line));
	if (ray->side == 0 && ray->dir.x > 0)
		tex_x = cube->img->size_line - tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex_x = cube->img->size_line - tex_x - 1;
	ray->step = 1.0 * cube->img->size_line /
		ft_wall_height(ray, WIN_HEIGHT);
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 +
					ft_wall_height(ray, WIN_HEIGHT) / 2) *
		ray->step;
	tex_y = (int)ray->tex_pos & (cube->img->size_line - 1);
	while (ray->draw_start < ray->draw_end)
	{
		ray->color = cube->img->data[cube->img->size_line * tex_y + tex_x];
		ft_render(ray, cube, ray->draw_start);
		ray->draw_start++;
		ray->tex_pos += ray->step;
		tex_y = (int)ray->tex_pos & (cube->img->size_line - 1);
	}
}


void	ft_render(t_ray *ray, t_cube *cube, int y)
{
	char	*dst;

	dst = cube->img->data + (y * cube->img->size_line + ray->x
			* (cube->img->bitsxpixel / 8));
	*(unsigned int *)dst = ray->color;
}


void	ft_draw_wall(t_ray *ray, t_cube *cube)
{
	int	wall_height;

	wall_height = ft_wall_height(ray, WIN_HEIGHT);
	ray->draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	ft_texture_coord(ray, cube);
}
  */

void	ft_wall_height(t_ray *ray)
{
	if (!ray->side)
		ray->perp_wall_dist = ray->side_dist.x
			- ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y
			- ray->delta_dist.y;
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
		ray->wall_x = cube->player->pos.y + ray->perp_wall_dist
			* ray->dir.y;
	}
	else
	{
		ray->wall_x = cube->player->pos.x + ray->perp_wall_dist
			* ray->dir.x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if ((!ray->side && ray->dir.x > 0) || (ray->side
			&& ray->dir.y < 0))
	{
		ray->tex.x = TEXTURE_WIDTH - ray->tex.x - 1;
	}
	ray->tex.x = abs((int)ray->tex.x);	//	Or fabs()?
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

	cube->texture->sky[0] = 0;
	cube->texture->sky[1] = 0;
	cube->texture->sky[2] = 0;
	cube->texture->floor[0] = 255;
	cube->texture->floor[1] = 255;
	cube->texture->floor[2] = 255;
	y = -1;
	while (++y < ray->draw_start)
	{
		put_pixel_in_image(cube->img, x, y,
				color_convert(cube->texture->sky[0], cube->texture->sky[1],
					cube->texture->sky[2]));
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
		put_pixel_in_image(cube->img, x, y,
				color_convert(cube->texture->floor[0],
					cube->texture->floor[1], cube->texture->floor[2]));
		y += 1;
	}
}
