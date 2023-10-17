/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:24:47 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/17 17:05:25 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	gotomap(char *line, int start, t_cube *cube)
{
	int	i;

	i = 0;
	while (i < start)
	{
		line = get_next_line(cube->fd);
		free(line);
		i++;
	}
}

int	is_mapstart(char *line, t_cube *cube)
{
	int	i;
	int	f;
	int	c;

	i = 0;
	f = 0;
	c = 0;
	while (i < 4 && cube->cardinal[i])
		i++;
	while (f < 3 && cube->colors[0][f] >= 0)
		f++;
	while (c < 3 && cube->colors[1][c] >= 0)
		c++;
	if (i == 4 && f == 3 && c == 3)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != '1' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
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
		cube->colors[0][0] = ft_atoi(rgb[0]);
		cube->colors[0][1] = ft_atoi(rgb[1]);
		cube->colors[0][2] = ft_atoi(rgb[2]);
	}
	if (type == CEILING)
	{
		cube->colors[1][0] = ft_atoi(rgb[0]);
		cube->colors[1][1] = ft_atoi(rgb[1]);
		cube->colors[1][2] = ft_atoi(rgb[2]);
	}
}

void	add_color(int type, char **tok, t_cube *cube)
{
	//	ex. "x,y,z" split + atoi + add (no spaces allowed)
	int	n;
	char	**rgb;

	n = 0;
	rgb = ft_split(tok[1], ',');
	while(rgb[n])
		n++;
	if (n > 3)
	{
		puterr(2);
		//	Free + exit
	}

	add_rgb(type, rgb, cube);
	n = -1;
	while(rgb[++n])
		free(rgb[n]);
	free(rgb);
}

void	add_path(char **tok, int i, int type, t_cube *cube)
{
	cube->cardinal[i] = type;
	cube->tex_path[i] = ft_strdup(tok[1]);
}

void	add_element(char **tok, int *id, int type, t_cube *cube)
{
	//	Check for duplicates n add
	int	i;

	if (type == FLOOR || type == CEILING)
	{
		add_color(type, tok, cube);
		return ;
	}
	i = 0;
	while (cube->cardinal && cube->cardinal[i])
	{
		if (cube->cardinal[i] == type)
		{
			free(cube->tex_path[i]);
			add_path(tok, i, type, cube);
			return ;
		}
		i++;
	}
	add_path(tok, *id, type, cube);
	(*id)++;
}
