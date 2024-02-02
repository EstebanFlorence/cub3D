/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:51:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/04 15:18:51 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_up(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x + cube->player.dir.x * MARGIN)] != 1)
		cube->player.pos.x += cube->player.dir.x * MOV_SPEED;
	if (cube->map.maprix
		[(int)(cube->player.pos.y + cube->player.dir.y * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y += cube->player.dir.y * MOV_SPEED;
}

void	move_down(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x - cube->player.dir.x * MARGIN)] != 1)
		cube->player.pos.x -= cube->player.dir.x * MOV_SPEED;
	if (cube->map.maprix
		[(int)(cube->player.pos.y - cube->player.dir.y * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y -= cube->player.dir.y * MOV_SPEED;
}

void	move_right(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x - cube->player.dir.y * MARGIN)] != 1)
		cube->player.pos.x -= cube->player.dir.y * MOV_SPEED;
	if (cube->map.maprix
		[(int)(cube->player.pos.y + cube->player.dir.x * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y += cube->player.dir.x * MOV_SPEED;
}

void	move_left(t_cube *cube)
{
	if (cube->map.maprix[(int)(cube->player.pos.y)]
		[(int)(cube->player.pos.x + cube->player.dir.y * MARGIN)] != 1)
		cube->player.pos.x += cube->player.dir.y * MOV_SPEED;
	if (cube->map.maprix
		[(int)(cube->player.pos.y - cube->player.dir.x * MARGIN)]
		[(int)(cube->player.pos.x)] != 1)
		cube->player.pos.y -= cube->player.dir.x * MOV_SPEED;
}
