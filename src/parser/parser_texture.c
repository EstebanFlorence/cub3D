/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:08:13 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/03 18:09:47 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_rgb(int type, char **rgb, t_cube *cube)
{
	if (type == FLOOR)
	{
		cube->texture.skyground[0]
			= color_convert(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	else if (type == CEILING)
	{
		cube->texture.skyground[1]
			= color_convert(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
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

void	add_path(char *path, int i, int type, t_cube *cube)
{
	cube->texture.cardinal[i] = type;
	cube->texture.path[i] = ft_strdup(path);
}

void	add_element(char **tok, int *id, int type, t_cube *cube)
{
	int		i;
	char	*path;

	if (type == FLOOR || type == CEILING)
	{
		add_color(type, tok, cube);
		return ;
	}
	i = 0;
	path = ft_strtrim(tok[1], "\n");
	while (i < 4 && cube->texture.cardinal[i])
	{
		if (cube->texture.cardinal[i] == type)
		{
			free(cube->texture.path[i]);
			add_path(path, i, type, cube);
			free(path);
			return ;
		}
		i++;
	}
	add_path(path, *id, type, cube);
	free(path);
	(*id)++;
}
