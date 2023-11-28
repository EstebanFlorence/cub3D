/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:44:09 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/28 15:35:10 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_plr_pov(t_cam *player, char dir)
{
	player->plane.x = 0;
	player->plane.y = 0;
	if (dir == 'N')
	{
		player->dir.y = -1;
		player->dir.x = 0;
		player->plane.y = 0;
		player->plane.x = -0.66;
	}
	else if (dir == 'S')
	{
		player->dir.y = 1;
		player->dir.x = 0;
		player->plane.y = 0;
		player->plane.x = 0.66;
	}
	else if (dir == 'E')
	{
		player->dir.y = 0;
		player->dir.x = -1;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	else if (dir == 'W')
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
			if (ft_strchr("NEWS", cube->map.maprix[i][j]))
			{
				cube->player.pos.x = i + 0.5;
				cube->player.pos.y = j + 0.5;
				set_plr_pov(&cube->player, cube->map.maprix[i][j]);
				cube->map.maprix[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
