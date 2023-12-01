/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:37:01 by  gcavanna         #+#    #+#             */
/*   Updated: 2023/12/01 19:52:06 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	color_convert(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	ft_init_ray(int x, t_cube *cube, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir.x = cube->player.dir.x + cube->player.plane.x
		* ray->camera_x;
	ray->dir.y = cube->player.dir.y + cube->player.plane.y
		* ray->camera_x;
	ray->map.x = (int)cube->player.pos.x;
	ray->map.y = (int)cube->player.pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);

	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
}

void	ft_init_side_distance(t_cube *cube, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (cube->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - cube->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (cube->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - cube->player.pos.y)
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
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step_y;
			ray->side = 1;
		}
		// if (ray->map.x < 0 || ray->map.y < 0 || ray->map.y >= cube->map.size.x || ray->map.x >= cube->map.size.y)
		// {
		// 	printf("ray->map.y = %f ", ray->map.y);
		// 	printf("cube->map.y = %f ", cube->map.size.y);
		// 	printf("ray coordinates are out of bounds\n");
		// 	return;
		// }
		printf("loco: %d\n", cube->map.maprix[(int)ray->map.x][(int)ray->map.y]);
		if (cube->map.maprix[(int)ray->map.x][(int)ray->map.y] == 1)
		{
			ray->hit = true;
		}
	}
}

void	ft_raycasting(t_cube *cube)
{
	int			x;
	t_ray		ray;

	cube->img = new_img(cube->mlx);
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
