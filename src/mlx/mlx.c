/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:48:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/12/02 19:30:39 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixelput(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->data + (y * img->size_line + x * (img->bitsxpixel / 8));
	*(unsigned int *)dst = color;
}

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

	window_loop(cube);

	return (0);
}

void	mlx_hooks(t_cube *cube)
{
	mlx_hook(cube->win, 2, 1L << 0, key_hook, cube);
	mlx_hook(cube->win, 17, 0, exit_hook, cube);
	//mlx_mouse_hook(cube->win, zoom_hook, cube);	Bonus?
	mlx_loop(cube->mlx);
}

void	mlx_innit(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!(cube->mlx))
		puterr(5);
	cube->win = mlx_new_window(cube->mlx, WIN_WIDTH, WIN_HEIGHT, \
									"Cub3D");
	if (!(cube->win))
		puterr(5);
	cube->img = malloc(sizeof(t_image));
	cube->img->ptr = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(cube->img))
		puterr(5);
	cube->img->data = mlx_get_data_addr(cube->img->ptr, \
						&cube->img->bitsxpixel, \
						&cube->img->size_line, \
						&cube->img->endian);
	if (!(cube->img->data))
		puterr(5);
}

int	exit_hook(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->texture.north.ptr);
	mlx_destroy_image(cube->mlx, cube->texture.south.ptr);
	mlx_destroy_image(cube->mlx, cube->texture.west.ptr);
	mlx_destroy_image(cube->mlx, cube->texture.east.ptr);
	mlx_destroy_image(cube->mlx, cube->img->ptr);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->img);
	free(cube->mlx);

	int	i;

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

void	mlx_destroy(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->img->ptr);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->img);
	free(cube->mlx);

	cube_destroy(cube);
}
