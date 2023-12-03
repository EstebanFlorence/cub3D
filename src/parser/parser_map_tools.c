/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:11:58 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/03 18:47:08 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	coordinate(char c)
{
	if (c == ' ' || c == '\n')
		return (-1);
	else if (c == '0')
		return (0);
	else if (c == '1')
		return (1);
	else if (c == 'N')
		return (NORTH);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'W')
		return (WEST);
	else if (c == 'E')
		return (EAST);
	return (-2);
}

void	map_index(t_index *index)
{
	index->i = -1;
	index->x = 0;
	index->y = -1;
}

int	linecmp(int i, char *prev_line, char *line)
{
	int	oldx;

	oldx = ft_strlen(prev_line) - 1;
	if (i >= oldx)
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

int	add_orient(char c, t_cube *cube)
{
	if (cube->map.orient)
		return (1);
	if (c == 'N')
		cube->map.orient = NORTH;
	else if (c == 'S')
		cube->map.orient = SOUTH;
	else if (c == 'E')
		cube->map.orient = EAST;
	else if (c == 'W')
		cube->map.orient = WEST;
	return (0);
}
