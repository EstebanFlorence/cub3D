/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:02:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/08 20:32:12 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parser(char **av)
{

}

int	innit(char **av, t_cube *cube)
{
	cube->mapath = ft_strjoin("./maps/", av[1]);
	if (open(cube->mapath, O_RDONLY) == -1)
	{
		write(STDERR_FILENO, "Error!\nInvalid path\n", 21);
		free(cube->mapath);
		//free(cube);
		return (1);
	}
	//	...
	return (0);
}

int	check(int ac, char **av)
{
	if (ac != 2)
	{
		write(STDERR_FILENO, "Error!\nWrong number of arguments\n", 34);
		//	Usage...
		return (1);
	}
	//	Check for map?
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	cube;

	if (check(ac, av))
		return (1);
	//cube = malloc(sizeof(t_cube));
	if (innit(av, &cube))
		return (1);
	//	mlx_innit()
	parser(av);


	//	destroy()
	return (0);
}
