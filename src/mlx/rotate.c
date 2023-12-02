/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:37:42 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/02 17:46:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_dx(t_cube *cube)
{
	double	dir_x;
	double	plane_x;

	dir_x = cube->player.dir.x;
	cube->player.dir.x = cube->player.dir.x * cos((-1) * ROT_SPEED)
						- cube->player.dir.y * sin((-1) * ROT_SPEED);
	cube->player.dir.y = dir_x * sin((-1) * ROT_SPEED) + cube->player.dir.y
						* cos((-1) * ROT_SPEED);
	plane_x = cube->player.plane.x;
	cube->player.plane.x = cube->player.plane.x * cos((-1) * ROT_SPEED)
							- cube->player.plane.y * sin((-1) * ROT_SPEED);
	cube->player.plane.y = plane_x * sin((-1) * ROT_SPEED) 
							- cube->player.plane.y;

}

void	rotate_sx(t_cube *cube)
{
	double	dir_x;
	double	plane_x;

	dir_x = cube->player.dir.x;
	cube->player.dir.x = cube->player.dir.x * cos(ROT_SPEED)
						- cube->player.dir.y * sin(ROT_SPEED);
	cube->player.dir.y = dir_x * sin(ROT_SPEED) + cube->player.dir.y
						* cos(ROT_SPEED);
	plane_x = cube->player.plane.x;
	cube->player.plane.x = cube->player.plane.x * cos(ROT_SPEED)
							- cube->player.plane.y * sin(ROT_SPEED);
	cube->player.plane.y = plane_x * sin(ROT_SPEED) 
							- cube->player.plane.y;
}
