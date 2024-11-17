/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:05:40 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/12 15:05:43 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <math.h>

static void	assign_player(t_vars *vars, int dir)
{
	if (dir == 0)
	{
		vars->player.p_angle = (3 * M_PI) / 2;
		vars->player.camera[X] = vars->player.pos[X];
		vars->player.camera[Y] = vars->player.pos[Y] - 1;
	}
	else if (dir == 1)
	{
		vars->player.p_angle = 0;
		vars->player.camera[X] = vars->player.pos[X] - 1;
		vars->player.camera[Y] = vars->player.pos[Y];
	}
	else if (dir == 2)
	{
		vars->player.p_angle = M_PI / 2;
		vars->player.camera[X] = vars->player.pos[X];
		vars->player.camera[Y] = vars->player.pos[Y] + 1;
	}
	else if (dir == 3)
	{
		vars->player.p_angle = M_PI;
		vars->player.camera[X] = vars->player.pos[X] + 1;
		vars->player.camera[Y] = vars->player.pos[Y];
	}
}

int	detect_player(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (vars->map[++y] != (void *)0)
	{
		x = -1;
		while (vars->map[y][++x])
		{
			vars->player.pos[X] = (x * TILE_SIZE) + TILE_SIZE / 2;
			vars->player.pos[Y] = (y * TILE_SIZE) + TILE_SIZE / 2;
			if (vars->map[y][x] == 'N')
				return (assign_player(vars, 0), 0);
			else if (vars->map[y][x] == 'E')
				return (assign_player(vars, 1), 0);
			else if (vars->map[y][x] == 'S')
				return (assign_player(vars, 2), 0);
			else if (vars->map[y][x] == 'W')
				return (assign_player(vars, 3), 0);
		}
	}
	vars->player.dir[X] = cos(vars->player.p_angle);
	vars->player.dir[Y] = sin(vars->player.p_angle);
	return (1);
}
