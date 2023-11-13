/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:40:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/11/12 16:46:22 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_frame_rendering(t_cube *cube)
{
	ft_raycasting(cube);
	mlx_clear_window(cube->mlx, cube->win);
	mlx_put_immage_to_window(cube->mlx, cube->win, cube->img.img_ptr, 0, 0);
}
