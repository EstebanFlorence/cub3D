/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/17 20:25:30 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	innit(char **av, t_map *map, t_cube *cube)
{
	cube->mapath = ft_strjoin("./maps/", av[1]);
	cube->fd = open(cube->mapath, O_RDONLY);
	if (cube->fd == -1)
	{
		free(cube->mapath);
		//free(cube);
		return (puterr(1));
	}
	cube->cardinal[0] = 0;
	cube->cardinal[1] = 0;
	cube->cardinal[2] = 0;
	cube->cardinal[3] = 0;
	cube->colors[0][0] = -1;
	cube->colors[0][1] = -1;
	cube->colors[0][2] = -1;
	cube->colors[1][0] = -1;
	cube->colors[1][1] = -1;
	cube->colors[1][2] = -1;

	cube->map = map;
	cube->map->n = false;
	cube->map->s = false;
	cube->map->e = false;
	cube->map->w = false;
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

void	destroy(t_cube *cube)
{
	int	i;

	free(cube->mapath);
	i = 0;
	while(i < 4 && cube->tex_path[i])
		free(cube->tex_path[i++]);
	//i = 0;
	//while(i < cube->y)
	//	free(cube->map[i++]);
}

int	main(int ac, char **av)
{
	t_cube	cube;
	t_map	map;

	if (check(ac))
		return (1);
	//cube = malloc(sizeof(t_cube));
	if (innit(av, &map, &cube))
		return (1);
	//	mlx_innit()
	parser(&cube);

	for (int i = 0; i < 4 && cube.cardinal[i]; i++)
		printf("cardinal: %d\t%s\n", cube.cardinal[i], cube.tex_path[i]);
	destroy(&cube);
	return (0);
}
