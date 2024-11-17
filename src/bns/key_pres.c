/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pres.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:05:14 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/12 15:07:01 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"

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

static void	check_other(int keycode, t_vars *vars)
{
	if (keycode == SHIFT && (vars->keys.key_d || vars->keys.key_s \
		|| vars->keys.key_w || vars->keys.key_a))
		vars->player.running = 2.50;
	if (keycode == 18)
		vars->player.gun_type = 0;
	if (keycode == 19)
		vars->player.gun_type = 1;
	if (keycode == 20)
		vars->player.gun_type = 2;
}

int	key_capture(int keycode, t_vars *vars)
{
	if (keycode == ESC)
	{
		if (vars->ui.menu == 1)
			close_windows(vars, 1, 0);
		mlx_mouse_show();
		vars->ui.time = get_time();
		vars->ui.menu = 1;
	}
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
	check_other(keycode, vars);
	return (0);
}
