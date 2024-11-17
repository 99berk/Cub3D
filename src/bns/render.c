/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:15:38 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/13 02:06:19 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"
#include "../../libft/libft.h"
#include <math.h>

int	get_canvas(t_vars *vars)
{
	if (fill_t_data(&vars->ui.mini_map, vars, (int)(vars->render.sc_width * \
		0.2), (int)(vars->render.sc_height * 0.2)) == NULL)
		return (err("Image init error!"), 1);
	if (!fill_t_data(&vars->img, vars, vars->render.sc_width,
			vars->render.sc_height))
		return (err("Image init error!"), 1);
	if (!fill_t_data(&vars->ui.gun_canvas, vars, 64 * TILE_GUN,
			64 * TILE_GUN))
		return (err("Image init error!"), 1);
	if (!fill_t_data(&vars->ui.ui_canvas, vars, vars->render.sc_width,
			vars->render.sc_height))
		return (err("Image init error!"), 1);
	if (!fill_t_data(&vars->ui.sprites_canvas, vars, vars->render.sc_width,
			vars->render.sc_height))
		return (err("Image init error!"), 1);
	return (0);
}

int	fill_background(t_vars *vars)
{
	int		i;
	int		color_floor;
	int		color_celing;

	color_floor = rgb_to_hex(vars->textures.floor_rgb[0], \
		vars->textures.floor_rgb[1], vars->textures.floor_rgb[2]);
	color_celing = rgb_to_hex(vars->textures.ceiling_rgb[0], \
		vars->textures.ceiling_rgb[1], vars->textures.ceiling_rgb[2]);
	i = -1;
	while (++i < (vars->render.sc_height * vars->render.sc_width))
	{
		if (i < vars->render.sc_width * vars->render.sc_height / 2)
			pixel_put(&vars->img, i % vars->render.sc_width, i
				/ vars->render.sc_width, color_celing);
		else
			pixel_put(&vars->img, i % vars->render.sc_width, i
				/ vars->render.sc_width, color_floor);
	}
	return (0);
}

int	render_things(t_vars *vars)
{
	int	i;

	if (vars->ui.menu)
	{
		mlx_clear_window(vars->mlx.mlx, vars->mlx.win);
		if (menu(vars))
			return (destroy_canvases(vars), close_windows(vars, 1, 0));
		destroy_canvases(vars);
		return (2);
	}
	fill_background(vars);
	make_transparent(vars, vars->ui.sprites_canvas);
	if (vars->game.diamond == 0)
		vars->player.life = 0;
	enemy_hit(vars);
	if (cast_rays(vars, -1))
		return (close_windows(vars, 1, 0));
	render_mini_map(vars);
	if (render_gun(vars))
		return (close_windows(vars, 1, 0));
	render_ui(vars);
	i = -1;
	while (++i < vars->game.spr_count)
		vars->sprites->on_sc = 0;
	return (0);
}

void	put_image_screen(t_vars *vars)
{
	mlx_clear_window(vars->mlx.mlx, vars->mlx.win);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->img.img, 0, 0);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->ui.sprites_canvas.img, 0, 0);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, \
		vars->ui.gun_canvas.img, (vars->render.sc_width / 2) - ((64 * TILE_GUN) \
		/ 2), vars->render.sc_height - (64 * TILE_GUN));
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->ui.mini_map.img, 0, 0);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->ui.ui_canvas.img, 0, 0);
}

int	render(void *ptr)
{
	t_vars	*vars;
	int		ret;

	vars = (t_vars *)ptr;
	vars->player.fov = vars->fov_angle * (M_PI / 180);
	if (get_canvas(vars))
		return (close_windows(vars, 1, 0));
	if (music(vars))
		return (close_windows(vars, 1, 1));
	ret = render_things(vars);
	if (ret == 1)
		return (close_windows(vars, 1, 0));
	if (ret == 2)
		return (0);
	put_image_screen(vars);
	move_player(vars, 0.0, 0.0);
	if (vars->game.spr_count)
		sprite_func(vars);
	destroy_canvases(vars);
	return (0);
}
