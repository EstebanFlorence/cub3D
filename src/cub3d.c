/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/25 17:22:19 by adi-nata         ###   ########.fr       */
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

	cube->map->oriented = false;
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
	//close(cube->fd);
	i = 0;
	if (cube->map->tex_path[i])
	{
		while(i < 4 && cube->map->tex_path[i])
			free(cube->map->tex_path[i++]);		
	}
	i = 0;
	while(i < cube->map->y)
		free(cube->map->maprix[i++]);
	free(cube->map->maprix);
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

	for (int i = 0; i < 4 && cube.map->cardinal[i]; i++)
		printf("cardinal: %d\t%s\n", cube.map->cardinal[i], cube.map->tex_path[i]);
	destroy(&cube);

	return (0);
}
