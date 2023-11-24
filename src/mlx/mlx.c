/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:48:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/24 23:06:25 by adi-nata         ###   ########.fr       */
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

int	key_hook(int key, t_cube *cube)
{
	if (key == B_ESC)
		exit_hook(cube);
	if (key == ARROW_UP)
		cube->player->pos.y -= POS_SHIFT;
	if (key == ARROW_DOWN)
		cube->player->pos.y += POS_SHIFT;
	if (key == ARROW_LEFT)
		cube->player->pos.x -= POS_SHIFT;
	if (key == ARROW_RIGHT)
		cube->player->pos.x += POS_SHIFT;
//	if (key == M_KEY || key == TAB_KEY)

	//raycaster(cube);
	//render(cube);
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
	mlx_destroy_image(cube->mlx, cube->img->ptr);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->img);
	free(cube->mlx);

	cube_destroy(cube);

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
