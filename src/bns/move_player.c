/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:21:38 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/13 17:21:56 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"
#include <math.h>
#define CAMERA_DISTANCE 10

static void	positions(t_vars *vars, double *x, double *y)
{
	if (vars->keys.key_w)
	{
		*x += cos(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
		*y += sin(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
	}
	if (vars->keys.key_s)
	{
		*x += -cos(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
		*y += -sin(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
	}
	if (vars->keys.key_a)
	{
		*x += sin(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
		*y += -cos(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
	}
	if (vars->keys.key_d)
	{
		*x += -sin(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
		*y += cos(vars->player.p_angle) * PLAYER_SPEED * vars->player.running;
	}
}

void	check_camera(t_vars *vars)
{
	int	pos_x;
	int	pos_y;

	vars->player.camera[X] = vars->player.pos[X] - cos(vars->player.p_angle)
		* CAMERA_DISTANCE;
	vars->player.camera[Y] = vars->player.pos[Y] - sin(vars->player.p_angle)
		* CAMERA_DISTANCE;
	pos_x = vars->player.camera[X] / TILE_SIZE;
	pos_y = vars->player.camera[Y] / TILE_SIZE;
	if (vars->map[pos_y][pos_x] == '1')
	{
		vars->player.camera[X] = vars->player.pos[X];
		vars->player.camera[Y] = vars->player.pos[Y];
	}
}

int	move_player(t_vars *vars, double x, double y)
{
	int	new_x;
	int	new_y;
	int	map_x;
	int	map_y;

	mouse_move(vars);
	positions(vars, &x, &y);
	new_x = (vars->player.pos[X] + x) / TILE_SIZE;
	new_y = (vars->player.pos[Y] + y) / TILE_SIZE;
	map_x = (vars->player.pos[X]) / TILE_SIZE;
	map_y = (vars->player.pos[Y]) / TILE_SIZE;
	if (vars->player.running != 1 && vars->fov_angle >= 64)
		vars->fov_angle--;
	else if (vars->player.running == 1 && vars->fov_angle < 66)
		vars->fov_angle++;
	if (double_counter(vars->map) < (new_y) || vars->map[new_y][map_x] == '1'
		|| vars->map[new_y][map_x] == 'B')
		y = 0;
	if ((int)ft_strlen(vars->map[map_y]) < (new_x)
		|| vars->map[map_y][new_x] == '1' || vars->map[map_y][new_x] == 'B')
		x = 0;
	vars->player.pos[X] += x;
	vars->player.pos[Y] += y;
	check_camera(vars);
	return (0);
}
