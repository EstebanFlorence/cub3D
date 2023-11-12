/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:44:09 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/12 19:43:54 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Sets the player's point of view based on the given direction.
 * @param map - The map struct containing the player's position.
 * @param dir - The direction the player is facing (N, S, E, W).
 */
void	set_plr_pov(t_map *map, char dir)
{
	map->posx = 0;
	map->posy = 0;
	if (dir == 'N')
	{
		map->posy = -1;
		map->posx = 0.66;
	}
	else if (dir == 'S')
	{
		map->posy = 1;
		map->posx = -0.66;
	}
	else if (dir == 'E')
	{
		map->posx = 1;
		map->posy = 0.66;
	}
	else if (dir == 'W')
	{
		map->posx = -1;
		map->posy = -0.66;
	}
}

/**
 * Gets the player's position from the map and sets the player's point of view.
 * @param cube - The cube struct containing the map and player information.
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
			if (strchr("NEWS", cube->map->maprix[i][j]))
			{
				cube->map->posx = i + 0.5;
				cube->map->posy = j + 0.5;
				set_plr_pov(cube->map, cube->map->maprix[i][j]);
				cube->map->maprix[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
