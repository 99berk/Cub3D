/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:05:56 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/12 15:06:00 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"

void	bg_image(t_data *data, t_data canvas, t_img_args args)
{
	int	alpha;

	args.pos[Y] = -1;
	while (++args.pos[Y] < args.original_height)
	{
		args.pos[X] = -1;
		while (++args.pos[X] < args.original_width)
		{
			alpha = (int)((((float)args.original_width - args.pos[X]) \
				/ args.original_width) * 255);
			args.tile[Y] = -1;
			while (++args.tile[Y] < args.tile_size)
			{
				args.tile[X] = -1;
				while (++args.tile[X] < args.tile_size)
					pixel_put(&canvas, (args.pos[X] * args.tile_size) + \
					args.tile[X] + args.pos_x, (args.pos[Y] * args.tile_size) + \
					args.tile[Y] + args.pos_y, (texture_color(data, args.pos[X],
								args.pos[Y]) & 0xFFFFFF) | (alpha << 24));
			}
		}
	}
}

void	menu_background(t_vars *vars)
{
	t_img_args	args;
	static int	ani = 0;

	args.original_height = 810;
	args.original_width = 540;
	args.pos_x = vars->render.sc_width - 540 * 1.1;
	args.pos_y = 0;
	args.tile_size = 1.1;
	if (get_time() - vars->ui.time > 80)
	{
		ani++;
		vars->ui.time = get_time();
		if (ani > 26)
			ani = 0;
	}
	bg_image(&vars->ui.mars[ani], vars->ui.ui_canvas, args);
}

int	finish_menu(t_vars *vars)
{
	int	pos[2];

	pos[X] = vars->render.sc_width / 2 - 236;
	pos[Y] = vars->render.sc_height * 0.2;
	if (vars->game.diamond == 0)
	{
		if (print_text(vars, "win", pos, 8))
			return (1);
	}
	else
		if (print_text(vars, "game over", pos, 8))
			return (1);
	pos[X] = (8 * 4 * 5) + 40;
	pos[Y] = vars->render.sc_height / 2;
	if (print_text(vars, "new game", pos, 5))
		return (1);
	pos[X] = (4 * 4 * 5) + 40;
	pos[Y] = vars->render.sc_height / 2 + 80;
	if (print_text(vars, "Quit", pos, 5))
		return (1);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->ui.ui_canvas.img, 0, 0);
	return (0);
}

int	start_menu(t_vars *vars)
{
	int	pos[2];

	pos[X] = 264;
	pos[Y] = vars->render.sc_height * 0.2;
	if (print_text(vars, "martian", pos, 8))
		return (1);
	if (!vars->game.start)
	{
		pos[X] = (5 * 4 * 5) + 40;
		pos[Y] = vars->render.sc_height / 2;
		if (print_text(vars, "start", pos, 5))
			return (1);
	}
	else
	{
		pos[X] = (8 * 4 * 5) + 40;
		pos[Y] = vars->render.sc_height / 2;
		if (print_text(vars, "continue", pos, 5))
			return (1);
	}
	pos[X] = (4 * 4 * 5) + 40;
	pos[Y] = vars->render.sc_height / 2 + 80;
	if (print_text(vars, "quit", pos, 5))
		return (1);
	return (0);
}

int	menu(t_vars *vars)
{
	t_img_args	args;

	menu_background(vars);
	if (vars->player.life <= 0 && finish_menu(vars))
		return (close_windows(vars, 1, 0));
	else if (vars->player.life > 0 && start_menu(vars))
		return (close_windows(vars, 1, 0));
	args.original_height = 155;
	args.original_width = 155;
	args.pos_x = 40;
	args.pos_y = vars->render.sc_height - 117;
	args.tile_size = 0.5;
	scale_up_image(&vars->ui.music[vars->ui.music_on], vars->ui.ui_canvas,
		args);
	return (mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
			vars->ui.ui_canvas.img, 0, 0), 0);
}
