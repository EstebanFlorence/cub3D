/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:05 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/12 19:54:58 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* void	add_pos(int start, t_cube *cube)
{
	char	*line;

	line = NULL;
	
} */

int	coordinate(int i, char *line)
{
	if (line[i] == ' ' || line[i] == '\n')
		return (-1);
	else if (line[i] == '0')
		return (0);
	else if (line[i] == '1')
		return (1);
	else if (line[i] == 'N')
		return (NORTH);
	else if (line[i] == 'S')
		return (SOUTH);
	else if (line[i] == 'W')
		return (WEST);
	else if (line[i] == 'E')
		return (EAST);
	return (-2);
}

void	fill_map(char *line, t_cube *cube)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	while (line && y < cube->map->y)
	{
		while (line[i])
		{
			cube->map->maprix[y][x] = coordinate(i, line);
			if (cube->map->maprix[y][x] > 1)
			{
				cube->player->pos_x = x;
				cube->player->pos_y = y;
			}
			x++;
			i++;
		}
		free(line);
		line = get_next_line(cube->fd);
		i = 0;
		while (x < cube->map->x)
			cube->map->maprix[y][x++] = -1;
		x = 0;
		y++;
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

int	linecmp(int i, char *prev_line, char *line)
{
	int	oldx;

	oldx = ft_strlen(prev_line);
	if (i > oldx)
	{
		if (line[i] != '1')
			return (1);
		return (0);
	}
	if (line[i] == ' ')
	{
		if (prev_line[i] != '1' && prev_line[i] != ' ')
			return (1);
	}
	return (0);
}

int	add_orient(char c, t_cube *cube)
{
	if (cube->map->oriented == true)
		return (1);
	if (c == 'N')
	{
		cube->map->oriented = true;
		cube->map->n = true;
	}
	else if (c == 'S')
	{
		cube->map->oriented = true;
		cube->map->s = true;
	}
	else if (c == 'E')
	{
		cube->map->oriented = true;
		cube->map->e = true;
	}
	else if (c == 'W')
	{
		cube->map->oriented = true;
		cube->map->w = true;
	}
	return (0);
}

int	line_walls(int i, char *line, t_cube *cube)
{
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
		{
			if (line[i - 1] != '1')
				return (1);
			while (line[i] == ' ')
				i++;
			if (line[i] != '1')
				return (1);
		}
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (add_orient(line[i], cube))
				return (1);
		}
		else if (line[i] != '1' && line[i] != '0')
			return (1);
		i++;
	}
	if (line[i - 1] != '1')
		return (1);
	return (0);
}

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
		len = is_map(prev_line, line, cube);
		if (!len)
		{
			free(line);
			free(prev_line);
			return (puterr(4));
		}
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
	cube->map->x = x;
	cube->map->y = y;
	cube->map->maprix = (int **)ft_calloc(y + 1, sizeof(int *));
	y = -1;
	while (++y < cube->map->y)
		cube->map->maprix[y] = (int *)ft_calloc(x + 1, sizeof(int));
	return (0);
}
