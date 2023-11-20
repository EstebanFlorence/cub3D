/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:44:09 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/20 11:05:50 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_plr_pov(t_play *player, char dir)
{
	player->pos_x = 0;
	player->pos_y = 0;
	if (dir == 'N')
	{
		player->pos_y = -1;
		player->pos_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->pos_y = 1;
		player->pos_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->pos_x = 1;
		player->pos_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->pos_x = -1;
		player->pos_y = -0.66;
	}
}

void	ft_get_play_pos(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < cube->map->y)
	{
		j = 0;
		while (j < cube->map->x)
		{
			if (ft_strchr("NEWS", cube->map->maprix[i][j]))
			{
				cube->player->pos_x = i + 0.5;
				cube->player->pos_y = j + 0.5;
				set_plr_pov(cube->player, cube->map->maprix[i][j]);
				cube->map->maprix[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
