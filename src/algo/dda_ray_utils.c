/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:58:00 by  gcavanna         #+#    #+#             */
/*   Updated: 2023/11/20 15:04:12 by gcavanna         ###   ########.fr       */
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
		ray->wall_x = cube->player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = cube->player->pos_y + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex_x = (int)(ray->wall_x * (double)(cube->img->size_line));
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = cube->img->size_line - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
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

void	ft_wall_height(t_cube *cube)
{
	if (!cube->ray->side)
		cube->ray->perp_wall_dist = cube->ray->side_dist_x
			- cube->ray->delta_dist_x;
	else
		cube->ray->perp_wall_dist = cube->ray->side_dist_y
			- cube->ray->delta_dist_y;
	cube->ray->line_height = (int)(WIN_HEIGHT / cube->ray->perp_wall_dist);
	cube->ray->draw_start = -cube->ray->line_height / 2 + WIN_HEIGHT / 2;
	if (cube->ray->draw_start < 0)
		cube->ray->draw_start = 0;
	cube->ray->draw_end = cube->ray->line_height / 2 + WIN_HEIGHT / 2;
	if (cube->ray->draw_end >= WIN_HEIGHT)
		cube->ray->draw_end = WIN_HEIGHT - 1;
}

void	ft_texture_coord(t_ray *ray, t_cube *cube)
{
	if (!ray->side)
	{
		ray->wall_x = cube->player->pos_y + ray->perp_wall_dist * ray->dir_y;
	}
	else
	{
		ray->wall_x = cube->player->pos_x + ray->perp_wall_dist * ray->dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if ((!ray->side && ray->dir_x > 0) || (ray->side && ray->dir_y < 0))
	{
		ray->tex_x = TEXTURE_WIDTH - ray->tex_x - 1;
	}
	ray->tex_x = abs(ray->tex_x);
	ray->step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	ray->tex_pos = (ray->draw_start - (WIN_HEIGHT / 2) + ray->line_height / 2)
		* ray->step;
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

void	draw_wall(t_cube *cube, t_ray *ray, int x)
{
	int	y;

	y = -1;
	while (++y < ray->draw_start)
	{
		put_pixel_in_image(cube->img, x, y,
				color_convert(cube->textures->sky[0], cube->textures->sky[1],
					cube->textures->sky[2]));
	}
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (TEXTURE_HEIGHT - 1);
		ray->tex_pos += ray->step;
		put_pixel_in_image(cube->img, x, y, get_color(cube, ray));
		y += 1;
	}
	while (y < WIN_HEIGHT)
	{
		put_pixel_in_image(cube->img, x, y,
				color_convert(cube->textures->floor[0],
				cube->textures->floor[1], cube->textures->floor[2]));
		y += 1;
	}
}
