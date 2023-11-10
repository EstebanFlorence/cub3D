/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/10 17:31:58 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	cube->map->maprix = NULL;
	cube->map->oriented = false;
	cube->map->n = false;
	cube->map->s = false;
	cube->map->e = false;
	cube->map->w = false;


}

int	innit(char **av, t_map *map, t_cube *cube)
{
	cube->mapath = ft_strjoin("./maps/", av[1]);
	cube->fd = open(cube->mapath, O_RDONLY);
	if (cube->fd == -1)
	{
		free(cube->mapath);
		return (puterr(1));
	}
	map_innit(cube, map);
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

void	destroy_cube(t_cube *cube)
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


void	ft_destroy(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->img->ptr);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->img);
	free(cube->mlx);
}

void	mlx_innit(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!(cube->mlx))
		puterr(5);
	cube->win = mlx_new_window(cube->mlx, WIN_WIDTH, WIN_HEIGHT, \
									"Cub3D");
	if (!(cube->win))
		puterr(5);
	cube->img->ptr = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(cube->img))
		puterr(5);
	cube->img->data = mlx_get_data_addr(cube->img->ptr, \
						&cube->img->bitsxpixel, \
						&cube->img->size_line, \
						&cube->img->endian);
	if (!(cube->img->data))
		puterr(5);
}


int	main(int ac, char **av)
{
	t_cube	cube;
	t_map	map;

	if (check(ac))
		return (1);
	if (innit(av, &map, &cube))
		return (1);
	parser(&cube);

	cube.img = malloc(sizeof(t_img));
	mlx_innit(&cube);
	ft_destroy(&cube);

	destroy_cube(&cube);
	return (0);
}
