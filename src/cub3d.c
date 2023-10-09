/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/09 19:37:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	puterr(int n)
{
	if (n == 0)
	{
		write(STDERR_FILENO, "Error!\nWrong number of arguments\n", 34);

	}
	else if (n == 1)
	{
		write(STDERR_FILENO, "Error!\nInvalid path for textures\n", 34);

	}
	else if (n == 2)
	{
		write(STDERR_FILENO, "Error!\nInvalid info for element\n", 33);

	}
	else if (n == 3)
	{
		write(STDERR_FILENO, "Error!\nInvalid identifier\n", 27);

	}

	return (1);
}

void	add_rgb(char **tok, int type, t_cube *cube)
{
	//	ex. "x, y, z" split + atoi + add

}

void	add_path(char **tok, int i, t_cube *cube)
{
	int	n;

	n = -1;
	while(tok[++n])
		n++;
	if (n > 2)
	{
		puterr(2);
		//	Free + exit
	}
	cube->paths[i] = ft_strdup(tok[1]);
}

void	add_element(char **tok, int *id, int type, t_cube *cube)
{
	//	Check for duplicates n add
	int	i;

	if (type == FLOOR || type == CEILING)
	{
		add_rgb(tok, type, cube);
		return ;
	}
	i = 0;
	while (cube->cardinal && cube->cardinal[i])
	{
		if (cube->cardinal[i] == type)
		{
			free(cube->paths[i]);
			add_path(tok, i, cube);
			return ;
		}
		i++;
	}
	add_path(tok, *id, cube);
}

int	check_next_line(char *line, int *id, t_cube *cube)
{
	int		n;
	char	**tok;

	if (!line)
		return (puterr(2));
	n = -1;
	tok = ft_split(line, ' ');
	if (!tok)
		return (puterr(2));
	while (tok[++n])
		n++;
	if (n > 4)
		return (puterr(2));


	if (ft_strncmp(tok[0], "NO", ft_strlen(tok[0])))
		add_element(tok, id, NORTH, cube);
	else if (ft_strncmp(tok[0], "SO", ft_strlen(tok[0])))
		add_element(tok, id, SOUTH, cube);
	else if (ft_strncmp(tok[0], "WE", ft_strlen(tok[0])))
		add_element(tok, id, WEST, cube);
	else if (ft_strncmp(tok[0], "EA", ft_strlen(tok[0])))
		add_element(tok, id, EAST, cube);
	else if (ft_strncmp(tok[0], "F", ft_strlen(tok[0])))
		add_element(tok, id, FLOOR, cube);
	else if (ft_strncmp(tok[0], "C", ft_strlen(tok[0])))
		add_element(tok, id, CEILING, cube);
	else
		return (puterr(3));


	return (0);
}

void	parser(t_cube *cube)
{
	int		i;
	char	*line;

	i = 0;
	while (42)
	{
		line = get_next_line(cube->fd);

		if (check_next_line(line, &i, cube))
		{
			//	Error
			//	Free
			break ;
		}

		free(line);
		i++;
	}
}

int	innit(char **av, t_cube *cube)
{
	cube->mapath = ft_strjoin("./maps/", av[1]);
	cube->fd = open(cube->mapath, O_RDONLY);
	if (cube->fd == -1)
	{
		free(cube->mapath);
		//free(cube);
		return (puterr(1));
	}
	//	...
	return (0);
}

int	check(int ac)
{
	if (ac != 2)
	{
		puterr(0);
		//	Usage...
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	cube;

	if (check(ac))
		return (1);
	//cube = malloc(sizeof(t_cube));
	if (innit(av, &cube))
		return (1);
	//	mlx_innit()
	parser(&cube);


	//	destroy()
	return (0);
}
