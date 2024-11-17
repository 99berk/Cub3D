/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:05:15 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/23 18:05:16 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"
#include <math.h>

int	button_press(t_vars *vars, int x, int y)
{
	if (y > vars->render.sc_height / 2 && y < vars->render.sc_height
		/ 2 + 40 && x < 360 && x > 40)
	{
		if (vars->player.life <= 0)
			return (new_game(vars));
		if (x > 240 && !vars->game.start)
			return (0);
		vars->d_time = get_time();
		mlx_mouse_hide();
		mlx_mouse_move(vars->mlx.win, vars->render.sc_width / 2,
			vars->render.sc_height / 2);
		return (vars->game.start = 1, vars->ui.menu = 0, 0);
	}
	if (y > vars->render.sc_height / 2 + 80
		&& y < vars->render.sc_height / 2 + 120
		&& x < 200
		&& x > 40)
		close_windows(vars, 1, 0);
	if (y > vars->render.sc_height - 117
		&& y < vars->render.sc_height - 42
		&& x < 115
		&& x > 40)
		vars->ui.music_on = !vars->ui.music_on;
	return (0);
}

int	mouse_func(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		if (vars->ui.menu)
			button_press(vars, x, y);
		else
		{
			if (vars->player.shoot == 0
				&& vars->ui.ammo[vars->player.gun_type] > 0)
			{
				vars->player.shoot = 1;
				vars->ui.ammo[vars->player.gun_type]--;
			}
		}
		if (vars->ui.ammo[vars->player.gun_type] == 0)
			return (0);
		vars->s_time = get_time();
	}
	return (0);
}

void	calc_direction(t_vars *vars, int x, int mx)
{
	vars->player.p_angle += nor_angle((mx - x) * 0.005);
	vars->player.dir[X] = cos(vars->player.p_angle);
	vars->player.dir[Y] = sin(vars->player.p_angle);
	vars->player.plane[X] = (-1 * sin(vars->player.p_angle))
		* tan((vars->player.fov / 2));
	vars->player.plane[Y] = cos(vars->player.p_angle)
		* tan(vars->player.fov / 2);
}

int	mouse_move(t_vars *vars)
{
	int			mx;
	int			my;
	static int	x = 0;

	if (vars->new_game)
	{
		vars->new_game = 0;
		x = 0;
	}
	mlx_mouse_get_pos(vars->mlx.win, &mx, &my);
	if (mx != 0 && x == 0)
		x = vars->render.sc_width / 2;
	if (mx > vars->render.sc_width || mx < 5)
	{
		x = vars->render.sc_width / 2;
		mlx_mouse_move(vars->mlx.win, vars->render.sc_width / 2,
			vars->render.sc_height / 2);
		mlx_mouse_get_pos(vars->mlx.win, &mx, &my);
	}
	calc_direction(vars, x, mx);
	x = mx;
	return (0);
}
