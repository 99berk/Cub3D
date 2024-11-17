/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pres.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:05:14 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/12 23:05:15 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/libft.h"
#include <math.h>

static void	positions(t_vars *vars, double *x, double *y)
{
	if (vars->keys.key_la)
		vars->player.p_angle -= 0.08;
	if (vars->keys.key_ra)
		vars->player.p_angle += 0.08;
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

	positions(vars, &x, &y);
	new_x = (vars->player.pos[X] + x) / TILE_SIZE;
	new_y = (vars->player.pos[Y] + y) / TILE_SIZE;
	map_x = (vars->player.pos[X]) / TILE_SIZE;
	map_y = (vars->player.pos[Y]) / TILE_SIZE;
	if (double_counter(vars->map) < (new_y) || vars->map[new_y][map_x] == '1')
		y = 0;
	if ((int)ft_strlen(vars->map[map_y]) < (new_x)
		|| vars->map[map_y][new_x] == '1')
		x = 0;
	vars->player.pos[X] += x;
	vars->player.pos[Y] += y;
	check_camera(vars);
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == ARROW_R)
		vars->keys.key_ra = 0;
	if (keycode == ARROW_L)
		vars->keys.key_la = 0;
	if (keycode == W)
		vars->keys.key_w = 0;
	if (keycode == S)
		vars->keys.key_s = 0;
	if (keycode == A)
		vars->keys.key_a = 0;
	if (keycode == D)
		vars->keys.key_d = 0;
	if (keycode == SHIFT)
		vars->player.running = 1;
	return (0);
}

int	key_capture(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		close_windows(vars);
	if (keycode == ARROW_R)
		vars->keys.key_ra = 1;
	if (keycode == ARROW_L)
		vars->keys.key_la = 1;
	if (keycode == W)
		vars->keys.key_w = 1;
	if (keycode == S)
		vars->keys.key_s = 1;
	if (keycode == A)
		vars->keys.key_a = 1;
	if (keycode == D)
		vars->keys.key_d = 1;
	if (keycode == SHIFT && (vars->keys.key_d || vars->keys.key_s
			|| vars->keys.key_w || vars->keys.key_a))
		vars->player.running = 2.50;
	return (0);
}
