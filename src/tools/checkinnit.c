/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinnit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:01:14 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/17 20:21:26 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rayplay_innit(t_cube *cube, t_ray *ray, t_play *player)
{
	cube->ray = ray;
	cube->player = player;
}


void	map_innit(t_cube *cube, t_map *map)
{
	cube->map = map;
	cube->map->tex_path[0] = NULL;
	cube->map->tex_path[1] = NULL;
	cube->map->tex_path[2] = NULL;
	cube->map->tex_path[3] = NULL;
	cube->map->cardinal[0] = 0;
	cube->map->cardinal[1] = 0;
	cube->map->cardinal[2] = 0;
	cube->map->cardinal[3] = 0;
	cube->map->colors[0][0] = -1;
	cube->map->colors[0][1] = -1;
	cube->map->colors[0][2] = -1;
	cube->map->colors[1][0] = -1;
	cube->map->colors[1][1] = -1;
	cube->map->colors[1][2] = -1;
	cube->map->x = 0;
	cube->map->y = 0;
	cube->map->orient = 0;
	cube->map->maprix = NULL;
	cube->map->oriented = false;
	cube->map->n = false;
	cube->map->s = false;
	cube->map->e = false;
	cube->map->w = false;


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
