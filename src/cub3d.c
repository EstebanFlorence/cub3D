/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/17 20:44:35 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cube_destroy(t_cube *cube)
{
	int	i;

	free(cube->mapath);
	i = 0;
	while (i < 4 && cube->map->tex_path[i])
		free(cube->map->tex_path[i++]);
	i = -1;
	if (cube->map->maprix)
	{
		while (++i < cube->map->y && cube->map->maprix[i])
			free(cube->map->maprix[i]);
		free(cube->map->maprix);
	}
}

void	setdir(t_cube *cube)
{
	if (cube->map->orient == NORTH)
	{
		cube->player->dir_x = 0;
		cube->player->dir_y = -1;
	}
	if (cube->map->orient == SOUTH)
	{
		cube->player->dir_x = 0;
		cube->player->dir_y = 1;
	}
	if (cube->map->orient == EAST)
	{
		cube->player->dir_x = 1;
		cube->player->dir_y = 0;
	}
	if (cube->map->orient == WEST)
	{
		cube->player->dir_x = -1;
		cube->player->dir_y = 0;
	}
}

void	starter(t_cube *cube)
{
	setdir(cube);
	cube->player->plane_x = 0;
	cube->player->plane_y = 0;
}

int	main(int ac, char **av)
{
	t_cube	cube;
	t_map	map;
	t_ray	ray;
	t_play	player;

	if (check(ac))
		return (1);
	if (cube_innit(av, &cube))
		return (1);
	map_innit(&cube, &map);
	rayplay_innit(&cube, &ray, &player);
	parser(&cube);

	starter(&cube);

	cube.img = malloc(sizeof(t_image));
	mlx_innit(&cube);
	mlx_hooks(&cube);
	mlx_destroy(&cube);


	cube_destroy(&cube);
	return (0);
}
