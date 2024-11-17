/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:58:39 by aaltinto          #+#    #+#             */
/*   Updated: 2024/09/23 11:58:31 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../minilibx/mlx.h"
#include <stdlib.h>

void	set_null(t_vars *vars)
{
	int	i;

	vars->map = NULL;
	vars->textures.ceiling = NULL;
	vars->textures.floor = NULL;
	i = -1;
	while (++i < 4)
	{
		vars->xpm[i].img = NULL;
		vars->textures.walls[i] = NULL;
	}
	vars->textures.walls[i] = NULL;
	vars->mlx.mlx = NULL;
	vars->mlx.win = NULL;
}

int	marche(t_vars *vars)
{
	vars->render.sc_height = 900;
	vars->render.sc_width = 1090;
	vars->render.flag = 0;
	vars->keys.key_a = 0;
	vars->keys.key_s = 0;
	vars->keys.key_d = 0;
	vars->keys.key_w = 0;
	vars->keys.key_la = 0;
	vars->keys.key_ra = 0;
	vars->player.running = 1;
	vars->fov_angle = 66;
	vars->player.fov = vars->fov_angle * (M_PI / 180);
	set_null(vars);
	return (0);
}

int	main(int ac, char **argv)
{
	t_vars	vars;

	if (ac != 2)
		return (err(ARG));
	marche(&vars);
	if (read_map(argv, &vars))
		return (abort_mission(&vars), 1);
	vars.mlx.mlx = mlx_init();
	if (!vars.mlx.mlx)
		return (abort_mission(&vars), err("Mlx init error"));
	vars.mlx.win = mlx_new_window(vars.mlx.mlx, vars.render.sc_width,
			vars.render.sc_height, "cub3D");
	if (!vars.mlx.win)
		return (abort_mission(&vars), err("Mlx window error"));
	if (get_textures(&vars))
		return (close_windows(&vars), 1);
	mlx_hook(vars.mlx.win, 17, 0, close_windows, &vars);
	mlx_hook(vars.mlx.win, 02, 0, key_capture, &vars);
	mlx_hook(vars.mlx.win, 03, 0, key_release, &vars);
	mlx_loop_hook(vars.mlx.mlx, render, (void *)(&vars));
	mlx_loop(vars.mlx.mlx);
	return (close_windows(&vars), 0);
}
