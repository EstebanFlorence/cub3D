/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/01 17:10:14 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	start(t_cube *cube)
{
	mlx_innit(cube);

	//raycaster(cube);

	ft_convert_image(cube);
	ft_get_cam_pos(cube);
	mlx_loop_hook(cube->mlx, window_loop, cube);
	mlx_hooks(cube);
	mlx_destroy(cube);
}

int	main(int ac, char **av)
{
	t_cube cube;

	if (check(ac))
		return (1);
	if (cube_innit(av, &cube))
		return (1);
	parser(&cube);
	start(&cube);
	cube_destroy(&cube);
	return (0);
}
