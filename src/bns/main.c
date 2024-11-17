/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:58:39 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/13 17:35:05 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"

int	main(int ac, char **argv)
{
	t_vars	vars;

	if (ac != 2)
		return (err(ARG));
	if (marche(&vars) || read_map(argv, &vars))
		return (abort_mission(&vars, 1, 0), 1);
	vars.mlx.mlx = mlx_init();
	if (!vars.mlx.mlx)
		return (abort_mission(&vars, 1, 0), err("Mlx init error"));
	vars.mlx.win = mlx_new_window(vars.mlx.mlx, vars.render.sc_width,
			vars.render.sc_height, "cub3d");
	if (!vars.mlx.win)
		return (abort_mission(&vars, 1, 0), err("Mlx window error"));
	if (get_textures(&vars) || get_magnum_sprites(&vars))
		return (close_windows(&vars, 1, 0), 1);
	if (get_num_sprites(&vars, 7, 10))
		return (close_windows(&vars, 1, 0), 1);
	mlx_hook(vars.mlx.win, 17, 0, close_windows, &vars);
	mlx_hook(vars.mlx.win, 02, 0, key_capture, &vars);
	mlx_hook(vars.mlx.win, 03, 0, key_release, &vars);
	mlx_hook(vars.mlx.win, 04, 0, mouse_func, &vars);
	mlx_loop_hook(vars.mlx.mlx, render, (void *)(&vars));
	mlx_loop(vars.mlx.mlx);
	return (close_windows(&vars, 1, 0), 0);
}
