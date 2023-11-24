/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/24 23:48:05 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start(t_cube *cube)
{
	cube->img = malloc(sizeof(t_image));
	mlx_innit(cube);
//	mlx_loop_hook(cube->mlx, window_loop, cube);
	mlx_hooks(cube);
	mlx_destroy(cube);

}

void	else_innit(t_cube *cube, t_map *map, t_tex *texture, t_cam *player)
{
	map_innit(cube, map);
	texture_innit(cube, texture);
	player_innit(cube, player);
	cube->img = NULL;
}

int	main(int ac, char **av)
{
	t_cube	cube;
	t_map	map;
	t_tex	texture;
	t_cam	player;
//	t_ray	ray;

	if (check(ac))
		return (1);
	if (cube_innit(av, &cube))
		return (1);
	else_innit(&cube, &map, &texture, &player);
	parser(&cube);
	start(&cube);
	cube_destroy(&cube);
	return (0);
}
