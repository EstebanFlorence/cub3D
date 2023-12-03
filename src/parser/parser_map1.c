/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:05 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/03 18:31:20 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* void	add_pos(int start, t_cube *cube)
{
	char	*line;

	line = NULL;
	
} */

int	is_map(char *prev_line, char *line, t_cube *cube)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (0);
	i++;
	if (line_walls(i, line, cube))
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid(line[i]))
			return (0);
		if (linecmp(i, prev_line, line))
			return (0);
		i++;
	}
	return (i);
}

int	map_sizecheck_len(int *len, char *line, char *prev_line, t_cube *cube)
{
	*len = is_map(prev_line, line, cube);
	if (!(*len))
	{
		free(line);
		free(prev_line);
		return (1);
	}
	return (0);
}

int	map_sizecheck(char *line, int *x, int *y, t_cube *cube)
{
	int		len;
	char	*prev_line;

	prev_line = ft_strdup(line);
	free(line);
	while (42)
	{
		line = get_next_line(cube->fd);
		if (!line)
		{
			get_next_close(prev_line, cube);
			return (0);
		}
		if (map_sizecheck_len(&len, line, prev_line, cube))
			return (puterr(4));
		free(prev_line);
		prev_line = ft_strdup(line);
		free(line);
		if (len > *x)
			*x = len;
		(*y)++;
		len = 0;
	}
	return (0);
}

int	mapalloc(char *line, t_cube *cube)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (line[x] && line[x] != '\n')
		x++;
	y++;
	if (map_sizecheck(line, &x, &y, cube) || y < 3)
		return (1);
	cube->map.size.x = x;
	cube->map.size.y = y;
	cube->map.maprix = (int **)ft_calloc(y + 1, sizeof(int *));
	y = -1;
	while (++y < cube->map.size.y)
		cube->map.maprix[y] = (int *)ft_calloc(x + 1, sizeof(int));
	return (0);
}

int	check_next_map(int start, char *line, t_cube *cube)
{
	if (mapalloc(line, cube))
		return (1);
	if (open_path(cube))
		return (1);
	add_map(start, cube);
	return (0);
}
