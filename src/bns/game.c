/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:42:47 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/12 17:42:50 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"
#include <math.h>

int	new_game(t_vars *vars)
{
	int	count;

	count = vars->game.spr_count;
	vars->new_game = 1;
	while (--count >= 0)
		fill_sprites(vars, count);
	vars->game.diamond = vars->game.diamond_org;
	vars->game.enemy_count = vars->game.enemy_org;
	vars->ui.ammo[0] = 30;
	vars->ui.ammo[1] = 30;
	vars->ui.ammo[2] = 3;
	detect_player(vars);
	vars->d_time = get_time();
	mlx_mouse_hide();
	mlx_mouse_move(vars->mlx.win, vars->render.sc_width / 2,
		vars->render.sc_height / 2);
	vars->player.life = 100;
	vars->ui.menu = 0;
	return (0);
}

void	collect_diamond(t_vars *vars, t_player player, t_sprite *sprites)
{
	int	pos[2];

	if (!sprites->is_diamond)
		return ;
	pos[X] = vars->render.sc_width / 2;
	pos[Y] = vars->render.sc_height * 0.22;
	if ((sprites->spr_pos[X] <= (player.camera[X] / TILE_SIZE) + 0.5 \
		&& sprites->spr_pos[X] >= (player.camera[X] / TILE_SIZE) - 0.5)
		&& (sprites->spr_pos[Y] <= (player.camera[Y] / TILE_SIZE) + 0.5 \
		&& sprites->spr_pos[Y] >= (player.camera[Y] / TILE_SIZE) - 0.5))
	{
		if (!vars->game.enemy_count && vars->game.diamond--)
			sprites->life = 0;
		else
			vars->d_time = get_time();
	}
	if (get_time() - vars->d_time < 3000)
	{
		if (vars->game.enemy_count)
			print_text(vars, "kill all the martians", pos, 3);
		else
			print_text(vars, "collect the diamonds", pos, 3);
	}
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win,
		vars->ui.ui_canvas.img, 0, 0);
}

void	spr_move(t_vars *vars, double *pos, int i)
{
	double	x;
	double	y;

	x = 0;
	y = 0;
	if (pos[X] > (vars->player.pos[X] / TILE_SIZE - 0.5))
		x -= 0.025;
	else
		x += 0.025;
	if (pos[Y] > (vars->player.pos[Y] / TILE_SIZE - 0.5))
		y -= 0.025;
	else
		y += 0.025;
	if (vars->map[(int)(round(pos[Y] + y +((y / fabs(y)) * 0.25f)))][(int) \
	(round(pos[X]))] != '1' && vars->map[(int)(round(pos[Y] + y +((y / fabs(y))
		* 0.25f)))][(int)(round(pos[X]))] != 'B')
		if (fabs((pos[Y] + y) - (vars->player.pos[Y] / TILE_SIZE - 0.5)) >= 0.1)
			vars->sprites[i].spr_pos[Y] += y;
	if (vars->map[(int)(round(pos[Y]))][(int)(round(pos[X] + x + ((x / fabs(x)) \
	* 0.25f)))] != '1' && vars->map[(int)(round(pos[Y]))][(int)(round(pos[X] \
	+ x + ((x / fabs(x)) * 0.25f)))] != 'B')
		if (fabs((pos[X] + x) - (vars->player.pos[X] / TILE_SIZE - 0.5)) >= 0.1)
			vars->sprites[i].spr_pos[X] += x;
}

void	sprite_func(t_vars *vars)
{
	int		i;
	double	*pos;
	double	dist;

	i = -1;
	while (++i < vars->game.spr_count)
	{
		if (vars->sprites[i].life <= 0)
			continue ;
		collect_diamond(vars, vars->player, &(vars->sprites[i]));
		dist = euclid_dist(vars->player.pos, vars->sprites[i].spr_pos);
		pos = vars->sprites[i].spr_pos;
		if (dist < 7 && dist > 0.75f && vars->sprites[i].is_enemy)
			spr_move(vars, pos, i);
	}
}
