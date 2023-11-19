/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:40:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/19 18:29:04 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	next_frame_rendering(t_cube *cube)
{
	ft_raycasting(cube);
	mlx_clear_window(cube->mlx, cube->win);
	//mlx_put_image_to_window(cube->mlx, cube->win, cube->img->ptr, 0, 0);
}
