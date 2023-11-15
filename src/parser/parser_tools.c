/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:24:47 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/26 20:18:54 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_orient(char **tok)
{
	if (ft_strncmp(tok[0], "NO", ft_strlen(tok[0])) == 0)
		return (1);
	else if (ft_strncmp(tok[0], "SO", ft_strlen(tok[0])) == 0)
		return (1);
	else if (ft_strncmp(tok[0], "WE", ft_strlen(tok[0])) == 0)
		return (1);
	else if (ft_strncmp(tok[0], "EA", ft_strlen(tok[0])) == 0)
		return (1);
	else if (ft_strncmp(tok[0], "F", ft_strlen(tok[0])) == 0)
		return (1);
	else if (ft_strncmp(tok[0], "C", ft_strlen(tok[0])) == 0)
		return (1);
	return (0);
}

int	is_valid(char c)
{
	if (c != '1' && c != ' ' && c != '\n' && c != '0'
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	is_mapstart(char *line, char **tok, t_cube *cube)
{
	int	i;
	int	f;
	int	c;

	if (is_orient(tok))
		return (0);
	i = 0;
	f = 0;
	c = 0;
	while (i < 4 && cube->map->cardinal[i])
		i++;
	while (f < 3 && cube->map->colors[0][f] >= 0)
		f++;
	while (c < 3 && cube->map->colors[1][c] >= 0)
		c++;
	if (i == 4 && f == 3 && c == 3)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != '1' && line[i] != ' '
				&& line[i] != '\t' && line[i] != '\n')
			{
				puterr(4);
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

void	add_rgb(int type, char **rgb, t_cube *cube)
{
	if (type == FLOOR)
	{
		cube->map->colors[0][0] = ft_atoi(rgb[0]);
		cube->map->colors[0][1] = ft_atoi(rgb[1]);
		cube->map->colors[0][2] = ft_atoi(rgb[2]);
	}
	if (type == CEILING)
	{
		cube->map->colors[1][0] = ft_atoi(rgb[0]);
		cube->map->colors[1][1] = ft_atoi(rgb[1]);
		cube->map->colors[1][2] = ft_atoi(rgb[2]);
	}
}

void	add_color(int type, char **tok, t_cube *cube)
{
	int		n;
	char	**rgb;

	n = 0;
	rgb = ft_split(tok[1], ',');
	while (rgb[n])
		n++;
	if (n > 3)
	{
		puterr(2);
		//	Free + exit
	}
	add_rgb(type, rgb, cube);
	n = -1;
	while (rgb[++n])
		free(rgb[n]);
	free(rgb);
}

void	add_path(char **tok, int i, int type, t_cube *cube)
{
	cube->map->cardinal[i] = type;
	cube->map->tex_path[i] = ft_strdup(tok[1]);
}

void	add_element(char **tok, int *id, int type, t_cube *cube)
{
	int	i;

	if (type == FLOOR || type == CEILING)
	{
		add_color(type, tok, cube);
		return ;
	}
	i = 0;
	while (i < 4 && cube->map->cardinal[i])
	{
		if (cube->map->cardinal[i] == type)
		{
			free(cube->map->tex_path[i]);
			add_path(tok, i, type, cube);
			return ;
		}
		i++;
	}
	add_path(tok, *id, type, cube);
	(*id)++;
}
