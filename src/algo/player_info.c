/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:44:09 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/28 16:30:16 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_plr_pov(t_cam *player, int dir)
{
	//printf("dir = %d\n", dir);
	if (dir == NORTH)
	{
		player->dir.y = -1;
		player->dir.x = 0;
		player->plane.y = 0;
		player->plane.x = -0.66;
	}
	else if (dir == SOUTH)
	{
		player->dir.y = 1;
		player->dir.x = 0;
		player->plane.y = 0;
		player->plane.x = 0.66;
	}
	else if (dir == EAST)
	{
		player->dir.y = 0;
		player->dir.x = -1;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else if (dir == WEST)
	{
		player->dir.y = 0;
		player->dir.x = 1;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
}

void	ft_get_cam_pos(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < cube->map.size.y)
	{
		j = 0;
		while (j < cube->map.size.x)
		{
			if (cube->map.maprix[i][j] >= 2 && cube->map.maprix[i][j] <= 5)
			{
				cube->player.pos.x = i + 0.5;
				cube->player.pos.y = j + 0.5;
				set_plr_pov(&cube->player, cube->map.maprix[i][j]);
				cube->map.maprix[i][j] = 0;
				return ;
			}
			j++;
		}
		i++;
	}
}
