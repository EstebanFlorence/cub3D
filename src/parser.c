/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:51 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/13 19:38:07 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_map()
{
	printf("Daje\n");
}

void	mapalloc_size(char *line, int *x, int *y, t_cube *cube)
{
	int	len;

	len = 0;
	while (42)
	{
		line = get_next_line(cube->fd);
		if (!line)
		{
			get_next_line(-42);
			close(cube->fd);
			break ;
		}
		while (line[len])
			len++;
		free(line);
		if (len > *x)
			*x = len;
		(*y)++;
		len = 0;
	}
}

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

void	mapalloc(int start, char *line, t_cube *cube)
{
	int		x;
	int		y;
	//char	*line;
	(void)start;
	//gotomap(line, start, cube);

	x = 0;
	y = 0;
	//line = get_next_line(cube->fd);
	while (line[x])
		x++;
	free(line);
	y++;

	mapalloc_size(line, &x, &y, cube);

	cube->map = (int **)ft_calloc(y, sizeof(int *));
	y = -1;
	while (cube->map[++y])
		cube->map[y] = (int *)ft_calloc(x, sizeof(int));
}

int	check_next_map(int start, char *line, t_cube *cube)
{
	//if (open_path(cube))
	//	return (1);
	mapalloc(start, line, cube);
	if (open_path(cube))
		return (1);
	add_map(cube);


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
	else if (is_map(line, cube))
	{
		*id = -1;
		return (0);
	}
	else if (!ft_strncmp(line, "\n", ft_strlen(line)))
		return (0);
	tok = ft_split(line, ' ');
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
			//	Error
			//	Free
			break ;
		}
		else if (i == -1)
		{
			//	Free + close fd + save line (n) where map starts and repeat
			//free(line);
			//get_next_line(-42);
			//close(cube->fd);
			if (check_next_map(n, line, cube))
			{
				//	Error
				//	Free
				break ;
			}
			break ;
		}
		free(line);
		n++;
	}
	printf("lines: %d\n", n);
}
