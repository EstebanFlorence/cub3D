/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:51 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/19 21:21:47 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_map(int start, t_cube *cube)
{
	char	*line;
	//(void)start;
	//(void)cube;
	//printf("Daje\n");
	line = NULL;
	gotomap(line, start, cube);
	


}

int	is_valid(char c)
{
	if (c != '1' && c != ' ' && c != '\n' && c != '0' &&
		c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
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
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
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
	int	i = 12;
	int		len;
	char	*prev_line;

	len = 0;
	prev_line = ft_strdup(line);
	free(line);
	while (42)
	{
		line = get_next_line(cube->fd);

		printf("map_sizecheck line: %d\n", i);
		i++;

		if (!line)
		{
			free(prev_line);
			get_next_line(-42);
			close(cube->fd);
			return (0);
		}
		len = is_map(prev_line, line, cube);
		if (!len)
		{
			puterr(4);
			//	Free + exit
			free(line);
			free(prev_line);
			return (1);
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
	if (map_sizecheck(line, &x, &y, cube))
		return (1);
	cube->map->x = x;
	cube->map->y = y;
	cube->map->maprix = (int **)ft_calloc(y, sizeof(int *));
	y = -1;
	while (++y < cube->map->y)
		cube->map->maprix[y] = (int *)ft_calloc(x, sizeof(int));
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

void	free_next_line(char **tok)
{
	int	i;

	i = -1;
	while(tok[++i])
		free(tok[i]);
	free(tok);

}

int	check_next_line(char *line, int *id, t_cube *cube)
{
	int		n;
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
	n = 0;
	while (tok[n])
		n++;
	if (n > 2)
		return (puterr(2));

	for (int i = 0; tok[i]; i++)
		printf("tok: %s\n", tok[i]);

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
	free_next_line(tok);
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
		if (check_next_line(line, &i, cube))
		{
			free(line);
			get_next_line(-42);
			destroy(cube);
			exit(EXIT_FAILURE);
		}
		else if (i == -1)
		{
			n++;
			if (check_next_map(n, line, cube))
			{
				get_next_line(-42);
				destroy(cube);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		free(line);
		n++;
	}
}
