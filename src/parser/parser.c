/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:51 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/03 18:43:00 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_next_line_tex(char **tok, int *id, t_cube *cube)
{
	int	n;

	n = 0;
	while (tok[n])
		n++;
	if (n > 2)
		return (puterr(2));
	if (ft_strncmp(tok[0], "NO", ft_strlen(tok[0])) == 0)
		add_element(tok, id, NORTH, cube);
	else if (ft_strncmp(tok[0], "SO", ft_strlen(tok[0])) == 0)
		add_element(tok, id, SOUTH, cube);
	else if (ft_strncmp(tok[0], "WE", ft_strlen(tok[0])) == 0)
		add_element(tok, id, WEST, cube);
	else if (ft_strncmp(tok[0], "EA", ft_strlen(tok[0])) == 0)
		add_element(tok, id, EAST, cube);
	else if (ft_strncmp(tok[0], "F", ft_strlen(tok[0])) == 0)
		add_element(tok, id, FLOOR, cube);
	else if (ft_strncmp(tok[0], "C", ft_strlen(tok[0])) == 0)
		add_element(tok, id, CEILING, cube);
	else
	{
		free_next_line(tok);
		return (puterr(3));
	}
	return (0);
}

int	check_next_line(char *line, int *id, t_cube *cube)
{
	char	**tok;

	if (!line)
		return (puterr(2));
	else if (!ft_strncmp(line, "\n", ft_strlen(line)))
		return (0);
	tok = ft_split(line, ' ');
	if (is_mapstart(line, tok, cube))
	{
		*id = -1;
		free_next_line(tok);
		return (0);
	}
	if (!tok)
		return (puterr(2));
	check_next_line_tex(tok, id, cube);
	free_next_line(tok);
	return (0);
}

int	parse_line(int *i, int *n, char *line, t_cube *cube)
{
	if (check_next_line(line, i, cube))
	{
		get_next_close(line, cube);
		cube_destroy(cube);
		exit(EXIT_FAILURE);
	}
	else if (*i == -1)
	{
		(*n)++;
		if (check_next_map(*n, line, cube))	// Ocio
		{
			get_next_line(-42);
			cube_destroy(cube);
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	return (0);
}

void	parser(t_cube *cube)
{
	int		i;
	int		n;
	char	*line;

	i = 0;
	n = 0;
	while (42)
	{
		line = get_next_line(cube->fd);
		if (parse_line(&i, &n, line, cube))
			break ;
		free(line);
		n++;
	}
}
/* 	x = 0;
	y = 0;
	while (y < cube->map.size.y)
	{
		while (x < cube->map.size.x)
		{
			printf("%d", cube->map.maprix[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	} */