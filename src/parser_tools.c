/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:24:47 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/12 23:19:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_map(char *line, t_cube *cube)
{
	int	i;

	i = -1;
	while (cube->cardinal[++i])
		i++;

	if (i == 4 && cube->colors[0] && cube->colors[1])
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != '1' || line[i] != ' ')
			{
				puterr(4);
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

/* void	add_rgb(char **tok, int type, t_cube *cube)
{
	//	ex. "x,y,z" split + atoi + add (no spaces allowed)

}
 */
void	add_path(char **tok, int i, int type, t_cube *cube)
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
	cube->cardinal[i] = type;
	cube->paths[i] = ft_strdup(tok[1]);
}

void	add_element(char **tok, int *id, int type, t_cube *cube)
{
	//	Check for duplicates n add
	int	i;

	if (type == FLOOR || type == CEILING)
	{
	//	add_rgb(tok, type, cube);
		return ;
	}
	i = 0;
	while (cube->cardinal && cube->cardinal[i])
	{
		if (cube->cardinal[i] == type)
		{
			free(cube->paths[i]);
			add_path(tok, i, type, cube);
			return ;
		}
		i++;
	}
	add_path(tok, *id, type, cube);
	(*id)++;
}
