/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:37:01 by  gcavanna         #+#    #+#             */
/*   Updated: 2023/11/19 18:00:52 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_ray	ft_init_ray(float camera_x, t_cube *cube)
{
	cube->ray->dir_x = cube->ray->dir_x + cube->player->plane_x * camera_x;
	cube->ray->dir_y = cube->ray->dir_y + cube->player->plane_y * camera_x;
	cube->ray->map_x = (int)cube->player->pos_x;
	cube->ray->map_y = (int)cube->player->pos_y;
	cube->ray->delta_dist_x = fabsf(1 / cube->ray->dir_x);
	cube->ray->delta_dist_y = fabsf(1 / cube->ray->dir_y);
	cube->ray->hit = 0;
	return (*cube->ray);
}

t_ray	ft_init_side_distance(t_cube *cube)
{
	t_ray	side_dist;

	if (cube->ray->dir_x < 0)
	{
		side_dist.step_x = -1;
		side_dist.dist_x = (cube->player->pos_x - cube->ray->map_x) * cube->ray->delta_dist_x;
	}
	else
	{
		side_dist.step_x = 1;
		side_dist.dist_x = (cube->ray->map_x + 1.0 - cube->player->pos_x)
			* cube->ray->delta_dist_x;
	}
	if (cube->ray->dir_y < 0)
	{
		side_dist.step_y = -1;
		side_dist.dist_y = (cube->player->pos_y - cube->ray->map_y) * cube->ray->delta_dist_y;
	}
	else
	{
		side_dist.step_y = 1;
		side_dist.dist_y = (cube->ray->map_y + 1.0 - cube->player->pos_y)
			* cube->ray->delta_dist_y;
	}
	return (side_dist);
}

int	ft_wall_collision_detection(t_cube *cube)
{
	while (cube->ray->hit == 0)
	{
		if (cube->ray->dist_x < cube->ray->dist_y)
		{
			cube->ray->dist_x += cube->ray->delta_dist_x;
			cube->ray->map_x += cube->ray->step_x;
			cube->ray->side = 0;
		}
		else
		{
			cube->ray->dist_y += cube->ray->delta_dist_y;
			cube->ray->map_y += cube->ray->step_y;
			cube->ray->side = 1;
		}
		if (cube->map->maprix[cube->ray->map_x][cube->ray->map_y] == 1)
			cube->ray->hit = 1;
	}
	return (cube->ray->side);
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
		cube->ray->side = ft_wall_collision_detection(cube);
		if (cube->ray->side == 0)
			cube->ray->perp_wall_dist = (cube->ray->map_x - cube->player->pos_x +
									(1 - cube->ray->step_x) / 2) /
				cube->ray->dir_x;
		else
			cube->ray->perp_wall_dist = (cube->ray->map_y - cube->player->pos_y +
									(1 - cube->ray->step_y) / 2) /
				cube->ray->dir_y;
		//cube->z_buffer[x] = cube->ray->perp_wall_dist;
		ft_draw_wall(&ray, cube);
		x++;
	}
}
