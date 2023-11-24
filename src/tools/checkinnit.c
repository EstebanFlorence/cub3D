/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinnit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:01:14 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/24 23:31:07 by adi-nata         ###   ########.fr       */
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

void	texture_innit(t_cube *cube, t_tex *texture)
{
	cube->texture = texture;
	cube->texture->cardinal[0] = 0;
	cube->texture->cardinal[1] = 0;
	cube->texture->cardinal[2] = 0;
	cube->texture->cardinal[3] = 0;
	cube->texture->path[0] = NULL;
	cube->texture->path[1] = NULL;
	cube->texture->path[2] = NULL;
	cube->texture->path[3] = NULL;
	cube->texture->skyground[0][0] = -1;
	cube->texture->skyground[0][1] = -1;
	cube->texture->skyground[0][2] = -1;
	cube->texture->skyground[1][0] = -1;
	cube->texture->skyground[1][1] = -1;
	cube->texture->skyground[1][2] = -1;

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
