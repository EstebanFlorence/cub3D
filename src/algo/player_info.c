/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:44:09 by gcavanna          #+#    #+#             */
/*   Updated: 2023/12/02 16:02:00 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
				cube->player.pos.x = j + 0.5;
				cube->player.pos.y = i + 0.5;
				set_plr_pov(&cube->player, cube->map.maprix[i][j]);
				cube->map.maprix[i][j] = 0;
				return ;
			}
			j++;
		}
		i++;
	}
}
