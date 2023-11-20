/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/20 14:35:04 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	raycaster(t_cube *cube)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cube->ray->camera_x = 2 * x / (float)WIN_WIDTH - 1;
		//cube->player->ray_dir_x = ;

		x++;
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

	next_frame_rendering(&cube);
	//cube.img = malloc(sizeof(t_image));
	mlx_innit(&cube);
	mlx_hooks(&cube);
	mlx_destroy(&cube);


	cube_destroy(&cube);
	return (0);
}
