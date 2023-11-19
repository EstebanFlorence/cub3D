/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:44:09 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/19 17:39:37 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Sets the player's point of view based on the given direction.
 * @param map - The map struct containing the player's position.
 * @param dir - The direction the player is facing (N, S, E, W).
 */
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

/**
 * Gets the player's position from the player and sets the player's point of view.
 * @param cube - The cube struct containing the player and player information.
 */
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
