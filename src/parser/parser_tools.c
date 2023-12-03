/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:24:47 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/03 18:43:19 by adi-nata         ###   ########.fr       */
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

void	mapstart_innit(int *i, int *f, int *c, t_cube *cube)
{
	*i = 0;
	*f = 0;
	*c = 0;
	while (*i < 4 && cube->texture.cardinal[*i])
		(*i)++;
	while (*f < 1 && cube->texture.skyground[0] >= 0)
		(*f)++;
	while (*c < 1 && cube->texture.skyground[1] >= 0)
		(*c)++;
}

int	is_mapstart(char *line, char **tok, t_cube *cube)
{
	int	i;
	int	f;
	int	c;

	if (is_orient(tok))
		return (0);
	mapstart_innit(&i, &f, &c, cube);
	if (i == 4 && f == 1 && c == 1)
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

void	free_next_line(char **tok)
{
	int	i;

	i = -1;
	while (tok[++i])
		free(tok[i]);
	free(tok);
}
