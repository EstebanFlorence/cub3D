/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:51 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/10 19:34:18 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	alloc_map(int start, t_cube *cube)
{
	int		len;
	int		x;
	int		y;
	char	*line;

	len = 0;
	x = 0;
	y = 0;
	while (y < start)
	{
		line = get_next_line(cube->fd);
		free(line);
		y++;
	}
	y = 0;
	line = get_next_line(cube->fd);
	while(line[x])
		x++;
	free(line);
	while (42)
	{
		line = get_next_line(cube->fd);
		while (line[len])
			len++;
		free(line);
		if (len > x)
			x = len;
		y++;
		len = 0;
	}
	cube->map = (int **)ft_calloc(y, sizeof(int *));
	y = -1;
	while (cube->map[++y])
		cube->map[y] = (int *)ft_calloc(x, sizeof(int));
}

void	add_map(char *line, t_cube *cube)
{

}

int	check_next_map(int start, t_cube *cube)
{
	int		len;
	int		x;
	int		y;
	char	*line;

	cube->fd = open(cube->mapath, O_RDONLY);
	if (cube->fd == -1)
	{
		free(cube->mapath);
		//free(cube);
		return (puterr(1));
	}


	return (0);
}

int	check_next_line(char *line, int *id, t_cube *cube)
{
	int		n;
	char	**tok;

	if (!line)
		return (puterr(2));
		
	if (is_map(line, cube))
	{
		*id = -1;
		return (0);
	}

	n = -1;
	tok = ft_split(line, ' ');
	if (!tok)
		return (puterr(2));
	while (tok[++n])
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
		return (puterr(3));

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
		if (i == -1)
		{
			//	Free + close fd + save line (n) where map starts and repeat
			free(line);
			get_next_line(-42);
			close(cube->fd);
			if (check_next_map(n, cube))
			{
				//	Error
				//	Free
				break ;
			}
		}

		free(line);
		//i++;
		n++;
	}
	printf("lines: %d\n", i);
}
