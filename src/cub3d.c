/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/28 15:37:56 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start(t_cube *cube)
{
	mlx_innit(cube);
	ft_convert_image(cube);
	ft_get_cam_pos(cube);
	mlx_loop_hook(cube->mlx, window_loop, cube);
	mlx_hooks(cube);
	mlx_destroy(cube);
}

/* void	else_innit(t_cube *cube, t_map *map, t_tex *texture, t_cam *player)
{
	t_cube	cube;

	map_innit(cube, map);
	texture_innit(cube, texture);
	//player_innit(cube, player);
	//cube->img = NULL;
} */
int	main(int ac, char **av)
{
	t_cube cube;

	//	t_ray	ray;
	if (check(ac))
		return (1);
	if (cube_innit(av, &cube))
		return (1);
	parser(&cube);
	start(&cube);
	cube_destroy(&cube);
	return (0);
}
