/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:13:39 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/04 11:23:58 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_map(char *line, t_cube *cube)
{
	t_index	index;

	map_index(&index);
	while (line && ++(index.y) < cube->map.size.y)
	{
		while (line[++(index.i)])
		{
			cube->map.maprix[index.y][index.x] = coordinate(line[index.i]);
			if (cube->map.maprix[index.y][index.x] > 1)
			{
				cube->player.pos.x = index.x;
				cube->player.pos.y = index.y;
			}
			(index.x)++;
		}
		free(line);
		line = get_next_line(cube->fd);
		index.i = 0;
		while (index.x < cube->map.size.x)
			cube->map.maprix[index.y][(index.x)++] = -1;
		index.x = 0;
	}
	get_next_line(-42);
	close(cube->fd);
}

void	gotomap(char **line, int start, t_cube *cube)
{
	int	i;

	*line = get_next_line(cube->fd);
	i = 1;
	while (i < start)
	{
		free(*line);
		*line = get_next_line(cube->fd);
		i++;
	}
}

void	add_map(int start, t_cube *cube)
{
	char	*line;

	line = NULL;
	gotomap(&line, start, cube);
	fill_map(line, cube);
}
