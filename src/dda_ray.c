/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:37:01 by  gcavanna         #+#    #+#             */
/*   Updated: 2023/11/12 16:01:25 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	ft_init_ray(float camera_x, t_cube *cube)
{
	t_ray	ray;

	ray.dir_x = cube->map->dir_x + cube->map->plane_x * camera_x;
	ray.dir_y = cube->map->dir_y + cube->map->plane_y * camera_x;
	ray.map_x = (int)cube->map->pos_x;
	ray.map_y = (int)cube->map->pos_y;
	ray.delta_dist_x = fabsf(1 / ray.dir_x);
	ray.delta_dist_y = fabsf(1 / ray.dir_y);
	ray.hit = 0;
	return (ray);
}

t_ray	ft_init_side_distance(t_ray ray, t_cube *cube)
{
	t_ray	side_dist;

	if (ray.dir_x < 0)
	{
		side_dist.step_x = -1;
		side_dist.dist_x = (cube->map->pos_x - ray.map_x) * ray.delta_dist_x;
	}
	else
	{
		side_dist.step_x = 1;
		side_dist.dist_x = (ray.map_x + 1.0 - cube->map->pos_x)
			* ray.delta_dist_x;
	}
	if (ray.dir_y < 0)
	{
		side_dist.step_y = -1;
		side_dist.dist_y = (cube->map->pos_y - ray.map_y) * ray.delta_dist_y;
	}
	else
	{
		side_dist.step_y = 1;
		side_dist.dist_y = (ray.map_y + 1.0 - cube->map->pos_y)
			* ray.delta_dist_y;
	}
	return (side_dist);
}

int	ft_wall_collision_detection(t_map *map, t_ray ray)
{
	while (ray.hit == 0)
	{
		if (ray.dist_x < ray.dist_y)
		{
			ray.dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (map->maprix[ray.map_x][ray.map_y] == 1)
			ray.hit = 1;
	}
	return (ray.side);
}

void	ft_raycasting(t_cube *cube)
{
	int		x;
	float	camera_x;
	t_ray	ray;
	t_ray	side_dist;

	x = 0;
	while (x < cube->win_width)
	{
		camera_x = 2 * x / (float)cube->win_width - 1;
		ray = ft_init_ray(camera_x, cube);
		side_dist = ft_init_side_distance(ray, cube);
		ray.side = ft_wall_collision_detection(cube->map, ray);
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - cube->map->pos_x +
									(1 - ray.step_x) / 2) /
				ray.dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - cube->map->pos_y +
									(1 - ray.step_y) / 2) /
				ray.dir_y;
		cube->z_buffer[x] = ray.perp_wall_dist;
		ft_draw_wall(&ray, cube);
		x++;
	}
}
