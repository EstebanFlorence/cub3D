/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:37:42 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/02 18:26:15 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_dx(t_cube *cube)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cube->player.dir.x;
	cube->player.dir.x = cube->player.dir.x * cos((-1) * ROT_SPEED)
		- cube->player.dir.y * sin((-1) * MOV_SPEED);
	cube->player.dir.y = olddirx * sin((-1) * MOV_SPEED) + cube->player.dir.y
		* cos((-1) * MOV_SPEED);
	oldplanex = cube->player.plane.x;
	cube->player.plane.x = cube->player.plane.x * cos((-1) * MOV_SPEED)
		- cube->player.plane.y * sin((-1) * MOV_SPEED);
	cube->player.plane.y = oldplanex * sin((-1) * MOV_SPEED)
		+ cube->player.plane.y * cos((-1) * MOV_SPEED);
}

void	rotate_sx(t_cube *cube)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cube->player.dir.x;
	cube->player.dir.x = cube->player.dir.x * cos(MOV_SPEED)
		- cube->player.dir.y * sin(MOV_SPEED);
	cube->player.dir.y = olddirx * sin(MOV_SPEED) + cube->player.dir.y
		* cos(MOV_SPEED);
	oldplanex = cube->player.plane.x;
	cube->player.plane.x = cube->player.plane.x * cos(MOV_SPEED)
		- cube->player.plane.y * sin(MOV_SPEED);
	cube->player.plane.y = oldplanex * sin(MOV_SPEED)
		+ cube->player.plane.y * cos(MOV_SPEED);
}
