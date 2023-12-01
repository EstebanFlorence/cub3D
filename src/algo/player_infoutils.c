/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_infoutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:55:34 by gcavanna          #+#    #+#             */
/*   Updated: 2023/12/01 18:54:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_plr_pov(t_cam *player, int dir)
{
	if (dir == NORTH)
		set_plr_pov_north(player);
	else if (dir == SOUTH)
		set_plr_pov_south(player);
	else if (dir == EAST)
		set_plr_pov_east(player);
	else if (dir == WEST)
		set_plr_pov_west(player);
}

void	set_plr_pov_north(t_cam *player)
{
	player->dir.y = -1;
	player->dir.x = 0;
	player->plane.y = 0;
	player->plane.x = -0.66;
}

void	set_plr_pov_south(t_cam *player)
{
	player->dir.y = 1;
	player->dir.x = 0;
	player->plane.y = 0;
	player->plane.x = 0.66;
}

void	set_plr_pov_east(t_cam *player)
{
	player->dir.y = 0;
	player->dir.x = -1;
	player->plane.x = 0;
	player->plane.y = 0.66;
}

void	set_plr_pov_west(t_cam *player)
{
	player->dir.y = 0;
	player->dir.x = 1;
	player->plane.x = 0;
	player->plane.y = -0.66;
}