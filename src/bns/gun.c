/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:06:05 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/13 17:35:05 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"
#include <stdlib.h>

int	enemy_hit(t_vars *vars)
{
	int	i;
	int	distance;
	int	closest[2];

	i = -1;
	closest[0] = -1;
	while (++i < vars->game.spr_count)
	{
		if (!vars->sprites[i].is_enemy || !vars->sprites[i].on_sc)
			continue ;
		distance = euclid_dist(vars->player.camera, vars->sprites[i].spr_pos);
		if (vars->sprites[i].is_enemy
			&& (closest[0] == -1 || distance < closest[0]))
		{
			closest[0] = distance;
			closest[1] = i;
		}
	}
	if (closest[0] != -1 && vars->player.shoot)
		vars->sprites[closest[1]].hit = 1;
	return (0);
}

void	calculate_ammo_count(t_vars *vars, double pos_tile)
{
	int			ammo;
	int			pos;
	t_img_args	args;

	ammo = vars->ui.ammo[vars->player.gun_type];
	pos = 0;
	args.original_height = 10;
	args.original_width = 7;
	args.tile_size = pos_tile;
	args.pos_x = vars->render.sc_width * 0.8 - pos * 7;
	args.pos_y = vars->render.sc_height * 0.8;
	while (ammo != 0)
	{
		args.pos_x = vars->render.sc_width * 0.8 - pos * 7;
		args.pos_y = vars->render.sc_height * 0.8;
		scale_up_image(&vars->ui.num[ammo % 10], vars->ui.ui_canvas, args);
		ammo /= 10;
		pos += pos_tile;
	}
	if (vars->ui.ammo[vars->player.gun_type] == 0)
		scale_up_image(&vars->ui.num[ammo % 10], vars->ui.ui_canvas, args);
}

static int	make_sound(t_vars *vars)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (err("Fork error"));
	if (vars->player.shoot == 1 && vars->player.ani_i == 0)
	{
		if (pid == 0)
		{
			if (!vars->player.gun_type)
				system("afplay guns/Huntershoot.wav");
			else if (vars->player.gun_type == 1)
				system("afplay guns/Talonshoot.wav");
			else
				system("afplay guns/Thermshoot.wav");
		}
	}
	if (pid == 0)
		close_windows(vars, 1, 1);
	return (0);
}

static int	shoot(t_vars *vars, int *gun)
{
	if (make_sound(vars))
		return (1);
	if ((int)(get_time() - vars->s_time) > 7 + vars->player.ani_i)
		vars->player.ani_i++;
	if ((*gun != 1 && vars->player.ani_i >= 10)
		|| (*gun == 1 && vars->player.ani_i >= 15))
	{
		vars->player.ani_i = 0;
		vars->player.shoot = 0;
	}
	return (0);
}

int	render_gun(t_vars *vars)
{
	t_img_args	args;
	static int	gun = 0;

	args.original_height = 64;
	args.original_width = 64;
	args.tile_size = TILE_GUN;
	args.pos_x = 0;
	args.pos_y = 0;
	if (vars->player.shoot == 1)
		if (shoot(vars, &gun))
			return (1);
	if (vars->player.ani_i == 0)
		gun = vars->player.gun_type;
	scale_up_image(&vars->gun[gun][vars->player.ani_i], vars->ui.gun_canvas,
		args);
	return (0);
}
