/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:48:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/11/19 17:59:41 by gcavanna         ###   ########.fr       */
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

void	set_winmap_coord(int x, int y, t_cube *cube)
{
	if (x % 10 == 0 || y % 10 == 0)
		pixelput(cube->img, x, y, 0x00FFFFFF);
	else
		pixelput(cube->img, x, y, 0x00000000);
}

void	set_win_coord(int x, int y, t_cube *cube)
{
	if (x % 100 == 0 || y % 100 == 0)
		pixelput(cube->img, x, y, 0x00FFFFFF);
	else
		pixelput(cube->img, x, y, 0x00000000);
}

void	set_map_coord(int x, int y, t_cube *cube)
{
	if (x % TILE_SIZE_X == 0 || y % TILE_SIZE_Y == 0)
		pixelput(cube->img, x, y, 0x00FFFFFF);

	else
		pixelput(cube->img, x, y, 0x00000000);

}

void	drawmap(t_cube *cube)
{
	int	x;
	int	y;

	x = 50;
	while (x <=  MAP_WIDTH + 50)
	{
		y = 50;
		while (y <= WIN_HEIGHT - 50 - MAP_HEIGHT)
		{
			set_map_coord(x, y, cube);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cube->mlx, \
		cube->win, cube->img->ptr, 0, 0);

}

void	render(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y <= WIN_HEIGHT)
	{
		x = 0;
		while (x <= WIN_WIDTH)
		{
			//set_win_coord(x, y, cube);
			set_winmap_coord(x, y, cube);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cube->mlx, \
		cube->win, cube->img->ptr, 0, 0);
}

int	key_hook(int key, t_cube *cube)
{
	if (key == B_ESC)
		exit_hook(cube);
	if (key == ARROW_UP)
		cube->player->pos_y -= POS_SHIFT;
	if (key == ARROW_DOWN)
		cube->player->pos_y += POS_SHIFT;
	if (key == ARROW_LEFT)
		cube->player->pos_x -= POS_SHIFT;
	if (key == ARROW_RIGHT)
		cube->player->pos_x += POS_SHIFT;
	if (key == M_KEY || key == TAB_KEY)
		drawmap(cube);

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