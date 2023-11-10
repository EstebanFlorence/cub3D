/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/10 20:04:45 by adi-nata         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_cube	cube;
	t_map	map;

	if (check(ac))
		return (1);
	if (cube_innit(av, &map, &cube))
		return (1);
	parser(&cube);

	cube.img = malloc(sizeof(t_image));
	mlx_innit(&cube);
	mlx_hooks(&cube);
	mlx_destroy(&cube);


	cube_destroy(&cube);
	return (0);
}
