/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:37:01 by  gcavanna         #+#    #+#             */
/*   Updated: 2023/11/24 22:31:13 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* t_ray	ft_init_ray(float camera_x, t_cube *cube)
{
	ray->dir.x = ray->dir.x + cube->player->plane.x * camera_x;
	ray->dir.y = ray->dir.y + cube->player->plane.y * camera_x;
	ray->map.x = (int)cube->player->pos.x;
	ray->map.y = (int)cube->player->pos.y;
	ray->delta_dist.x = fabsf(1 / ray->dir.x);
	ray->delta_dist.y = fabsf(1 / ray->dir.y);
	ray->hit = 0;
	return (*ray);
}

t_ray	ft_init_side_distance(t_cube *cube)
{
	t_ray	side_dist;

	if (ray->dir.x < 0)
	{
		side_dist.step_x = -1;
		side_dist.dist_x = (cube->player->pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		side_dist.step_x = 1;
		side_dist.dist_x = (ray->map.x + 1.0 - cube->player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		side_dist.step_y = -1;
		side_dist.dist_y = (cube->player->pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		side_dist.step_y = 1;
		side_dist.dist_y = (ray->map.y + 1.0 - cube->player->pos.y)
			* ray->delta_dist.y;
	}
	return (side_dist);
}

int	ft_wall_collision_detection(t_cube *cube)
{
	while (ray->hit == 0)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_dist.x;
			ray->map.x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delta_dist.y;
			ray->map.y += ray->step_y;
			ray->side = 1;
		}
		if (cube->map->maprix[ray->map.x][ray->map.y] == 1)
			ray->hit = 1;
	}
	return (ray->side);
}

void	ft_raycasting(t_cube *cube)
{
	int		x;
	float	camera_x;
	t_ray	ray;

	//t_ray	side_dist;
	//cube->img = new_img(cube->mlx);
	x = 0;
	while (x < WIN_HEIGHT)
	{
		camera_x = 2 * x / (float)WIN_HEIGHT - 1;
		ray = ft_init_ray(camera_x, cube);
		//side_dist = ft_init_side_distance(cube);
		ray->side = ft_wall_collision_detection(cube);
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map.x - cube->player->pos.x
					+
									(1 - ray->step_x) / 2) /
				ray->dir.x;
		else
			ray->perp_wall_dist = (ray->map.y - cube->player->pos.y
					+
									(1 - ray->step_y) / 2) /
				ray->dir.y;
		//cube->z_buffer[x] = ray->perp_wall_dist;
		ft_draw_wall(&ray, cube);
		x++;
	}
}
 */

unsigned int	color_convert(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	ft_init_ray(int x, t_cube *cube, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir.x = cube->player->dir.x + cube->player->plane.x
		* ray->camera_x;
	ray->dir.y = cube->player->dir.y + cube->player->plane.y
		* ray->camera_x;
	ray->map.x = (int)cube->player->pos.x;
	ray->map.y = (int)cube->player->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
}

void	ft_init_side_distance(t_cube *cube, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (cube->player->pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map.x + 1.0f - cube->player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (cube->player->pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map.y + 1.0f - cube->player->pos.y)
			* ray->delta_dist.y;
	}
}

void	ft_wall_collision_detection(t_cube *cube, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step_x;
			ray->side = 1;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step_y;
			ray->side = 1;
		}
		//printf("Y %d\n", ray->map.y);
		//printf("X %d\n", ray->map.x);
		if (cube->map->maprix[(int)ray->map.y][(int)ray->map.x] == 1)
			ray->hit = true;
	}
}

void	ft_raycasting(t_cube *cube)
{
	int			x;
	t_ray		ray;

//	cube->img = new_img(cube->mlx);	Già allocato in main(), se qui free()?
	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_init_ray(x, cube, &ray);
		ft_init_side_distance(cube, &ray);
		ft_wall_collision_detection(cube, &ray);
		ft_wall_height(&ray);
		ft_texture_coord(cube, &ray);
		draw_wall(x, cube, &ray);
		x += 1;
	}
}
