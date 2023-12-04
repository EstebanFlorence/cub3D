/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:13:39 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/04 16:52:57 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_player(t_index *index, t_cube *cube)
{
	if (cube->map.maprix[index->y][index->x] > 1)
	{
		cube->player.pos.x = index->x;
		cube->player.pos.y = index->y;
	}
}

int	fill_map(char *line, t_cube *cube)
{
	t_index	index;

	map_index(&index);
	while (line && ++(index.y) < cube->map.size.y)
	{
		while (line[++(index.i)])
		{
			cube->map.maprix[index.y][index.x] = coordinate(line[index.i]);
			put_player(&index, cube);
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
	if (cube->player.pos.x == -1 && cube->player.pos.y == -1)
		return (1);
	return (0);
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

int	add_map(int start, t_cube *cube)
{
	char	*line;

	line = NULL;
	gotomap(&line, start, cube);
	if (fill_map(line, cube))
		return (1);
	return (0);
}
