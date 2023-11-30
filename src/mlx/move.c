/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:51:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/29 18:13:53 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//	cube->player.speed to MOV_SPEED?

void	move_left(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x - cube->player.dir.y * MARGIN)] != 1)
		cube->player.pos.x -= cube->player.dir.y * cube->player.speed;
	if (cube->map.maprix[(int)(cube->player.pos.y + cube->player.dir.x * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y += cube->player.dir.x * cube->player.speed;
}

void	move_right(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x + cube->player.dir.y * MARGIN)] != 1)
		cube->player.pos.x += cube->player.dir.y * cube->player.speed;
	if (cube->map.maprix[(int)(cube->player.pos.y - cube->player.dir.x * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y -= cube->player.dir.x * cube->player.speed;
}

void	move_up(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x + cube->player.dir.x * MARGIN)] != 1)
		cube->player.pos.x += cube->player.dir.x * cube->player.speed;
	if (cube->map.maprix[(int)(cube->player.pos.y + cube->player.dir.y * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y += cube->player.dir.y * cube->player.speed;
}

void	move_down(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x - cube->player.dir.x * MARGIN)] != 1)
		cube->player.pos.x -= cube->player.dir.x * cube->player.speed;
	if (cube->map.maprix[(int)(cube->player.pos.y - cube->player.dir.y * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y -= cube->player.dir.y * cube->player.speed;
}
/* 
void	move_player(t_cube *cube)
{		
	if (cube->wasd_movement[0] == true)
		move_up(cube);
	if (cube->wasd_movement[1] == true)
		move_left(cube);
	if (cube->wasd_movement[2] == true)
		move_down(cube);
	if (cube->wasd_movement[3] == true)
		move_right(cube);
	if (cube->wasd_movement[5] == true)
		rotate_right(cube);
	if (cube->wasd_movement[4] == true)
		rotate_left(cube);
	if (cube->wasd_movement[6] == true)
		speed_up(cube);
	else if (cube->wasd_movement[6] == false)
		cube->player.speed = MOV_SPEED;
}
 */