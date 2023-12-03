/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkinnit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:01:14 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/03 21:50:56 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_innit(t_cube *cube)
{
	cube->texture.cardinal[0] = 0;
	cube->texture.cardinal[1] = 0;
	cube->texture.cardinal[2] = 0;
	cube->texture.cardinal[3] = 0;
	cube->texture.path[0] = NULL;
	cube->texture.path[1] = NULL;
	cube->texture.path[2] = NULL;
	cube->texture.path[3] = NULL;
	cube->texture.skyground[0] = -1;
	cube->texture.skyground[1] = -1;
	cube->texture.north.ptr = NULL;
	cube->texture.south.ptr = NULL;
	cube->texture.east.ptr = NULL;
	cube->texture.west.ptr = NULL;
}

void	map_innit(t_cube *cube)
{
	cube->map.size.x = 0;
	cube->map.size.y = 0;
	cube->map.orient = 0;
	cube->map.maprix = NULL;
}

int	check_file(char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (!file[i] || file[i--] != 'b')
		return (1);
	if (!file[i] || file[i--] != 'u')
		return (1);
	if (!file[i] || file[i--] != 'c')
		return (1);
	if (!file[i] || file[i--] != '.')
		return (1);
	return (0);
}

int	cube_innit(char **av, t_cube *cube)
{
	if (check_file(av[1]))
		return (puterr(3));
	cube->mapath = ft_strjoin("./maps/", av[1]);
	cube->fd = open(cube->mapath, O_RDONLY);
	if (cube->fd == -1)
	{
		free(cube->mapath);
		return (puterr(1));
	}
	texture_innit(cube);
	map_innit(cube);
	return (0);
}

int	check(int ac)
{
	if (ac != 2)
	{
		puterr(0);
		return (1);
	}
	return (0);
}
