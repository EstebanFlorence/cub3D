/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:32:57 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/29 17:49:10 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_innit(int x, double *camerax, t_ray *ray, t_cube *cube)
{
	ray->map.x = cube->player.pos.x;
	ray->map.y = cube->player.pos.y;
//	camerax = 2 * 
}

void	raycaster(t_cube *cube)
{
	int		x;
	double	camerax;
	t_ray	ray;

	x = 0;
	//put_skyground(cube);
	while (x < WIN_WIDTH)
	{
		ray_innit(x, &camerax, &ray, cube);
		
		x++;
	}


}
