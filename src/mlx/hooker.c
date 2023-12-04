/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:36:47 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/04 12:09:33 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mov_backnforth(int key, t_cube *cube)
{
	if (key == W_KEY)
		move_up(cube);
	if (key == S_KEY)
		move_down(cube);
}

void	mov_leftnright(int key, t_cube *cube)
{
	if (key == A_KEY)
		move_left(cube);
	if (key == D_KEY)
		move_right(cube);
}

int	exit_hook(t_cube *cube)
{
	int	i;

	mlx_destroy(cube);
	free(cube->mapath);
	i = 0;
	while (i < 4 && cube->texture.path[i])
		free(cube->texture.path[i++]);
	i = -1;
	if (cube->map.maprix)
	{
		while (++i < cube->map.size.y && cube->map.maprix[i])
			free(cube->map.maprix[i]);
		free(cube->map.maprix);
	}
	exit (EXIT_SUCCESS);
	return (0);
}

int	key_hook(int key, t_cube *cube)
{
	if (key == B_ESC)
		exit_hook(cube);
	if (key == W_KEY || key == S_KEY)
		mov_backnforth(key, cube);
	if (key == A_KEY || key == D_KEY)
		mov_leftnright(key, cube);
	if (key == ARROW_LEFT)
		rotate_sx(cube);
	if (key == ARROW_RIGHT)
		rotate_dx(cube);
	printf("position => x: %f , y: %f\n", cube->player.pos.x, cube->player.pos.y);
	window_loop(cube);
	return (0);
}

void	mlx_hooks(t_cube *cube)
{
	mlx_hook(cube->win, 2, 1L << 0, key_hook, cube);
	mlx_hook(cube->win, 17, 0, exit_hook, cube);
	mlx_loop(cube->mlx);
}
