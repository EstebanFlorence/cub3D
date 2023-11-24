/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinnit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:01:14 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/24 23:25:31 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	player_innit(t_cube *cube, t_cam *player)
{
	cube->player = player;
	if (cube->map->orient == NORTH)
	{
		cube->player->dir.x = 0;
		cube->player->dir.y = -1;
	}
	if (cube->map->orient == SOUTH)
	{
		cube->player->dir.x = 0;
		cube->player->dir.y = 1;
	}
	if (cube->map->orient == EAST)
	{
		cube->player->dir.x = 1;
		cube->player->dir.y = 0;
	}
	if (cube->map->orient == WEST)
	{
		cube->player->dir.x = -1;
		cube->player->dir.y = 0;
	}
	cube->player->plane.x = 0;
	cube->player->plane.y = 0;
}

void	map_innit(t_cube *cube, t_map *map)
{
	cube->map = map;

//	cube->map->width = 0;
//	cube->map->height = 0;
	cube->map->size.x = 0;
	cube->map->size.y = 0;
	cube->map->orient = 0;
	cube->map->maprix = NULL;

}

int		cube_innit(char **av, t_cube *cube)
{
	cube->mapath = ft_strjoin("./maps/", av[1]);
	cube->fd = open(cube->mapath, O_RDONLY);
	if (cube->fd == -1)
	{
		free(cube->mapath);
		return (puterr(1));
	}
	//map_innit(cube);
	//ray_innit(cube);
	return (0);
}

int	check(int ac)
{
	if (ac != 2)
	{
		puterr(0);
		//	Usage...
		return (1);
	}
	return (0);
}
