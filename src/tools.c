/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:00:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/10 16:00:52 by adi-nata         ###   ########.fr       */
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
	else if (n == 4)
	{
		write(STDERR_FILENO, "Error!\nInvalid info for map", 28);

	}

	return (1);
}
