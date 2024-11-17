/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:59:15 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/26 18:59:22 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"
#include <stdlib.h>
#include <signal.h>

void	scale_up_image(t_data *data, t_data canvas, t_img_args args)
{
	int	pos[2];
	int	tile[2];

	pos[Y] = -1;
	while (++pos[Y] < args.original_height)
	{
		pos[X] = -1;
		while (++pos[X] < args.original_width)
		{
			tile[Y] = -1;
			while (++tile[Y] < args.tile_size)
			{
				tile[X] = -1;
				while (++tile[X] < args.tile_size)
				{
					pixel_put(&canvas, (pos[X] * args.tile_size) + tile[X]
						+ args.pos_x, (pos[Y] * args.tile_size) + tile[Y]
						+ args.pos_y, texture_color(data, pos[X], pos[Y]));
				}
			}
		}
	}
}

int	select_index(t_vars *vars)
{
	if (vars->player.life == 100)
		return (0);
	if (vars->player.life == 75)
		return (1);
	if (vars->player.life == 50)
		return (2);
	if (vars->player.life == 25)
		return (3);
	return (3);
}

char	*pick_sound(t_vars *vars)
{
	char		*sound;

	if (vars->ui.menu == 1)
		sound = vars->ui.sound[0];
	else
		sound = vars->ui.sound[1];
	return (sound);
}

int	music(t_vars *vars)
{
	static int	s = -1;
	static int	m = 1;

	if (!vars->ui.music_on)
	{
		if (m == 1)
			kill(vars->game.pid + 1, SIGKILL);
		return (s = -1, m = 0, 0);
	}
	if (s != -1 && s == vars->ui.menu)
		return (0);
	else if (s != -1)
		kill(vars->game.pid + 1, SIGKILL);
	m = 1;
	vars->game.pid = fork();
	if (vars->game.pid < 0)
		return (err("Fork error"));
	if (vars->game.pid == 0)
	{
		system(pick_sound(vars));
		close_windows(vars, 1, 1);
	}
	s = vars->ui.menu;
	return (0);
}

void	render_ui(t_vars *vars)
{
	int			i;
	t_img_args	args;

	make_transparent(vars, vars->ui.ui_canvas);
	args.original_height = 48;
	args.original_width = 48;
	args.tile_size = 0.5;
	args.pos_x = vars->render.sc_width * 0.2 / 2 - 12;
	args.pos_y = vars->render.sc_height * 0.2 / 2 - 12;
	scale_up_image(&vars->ui.map_arrow, vars->ui.ui_canvas, args);
	calculate_ammo_count(vars, 3.5);
	args.original_height = 97;
	args.original_width = 380;
	args.pos_x = vars->render.sc_width * 0.9 - 100;
	args.pos_y = vars->render.sc_height * 0.9;
	args.tile_size = 0.5;
	i = select_index(vars);
	scale_up_image(&vars->ui.healt_bar[i], vars->ui.ui_canvas, args);
}
