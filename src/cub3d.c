/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/26 14:34:02 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_image	init_img(void)
{
	return ((t_image)
		{
			.ptr = NULL,
			.data = NULL,
			.width = 0,
			.height = 0,
			.bitsxpixel = 0,
			.size_line = 0,
			.endian = 0
		});
}

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
	//cube->img = NULL;
	init_img();
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
