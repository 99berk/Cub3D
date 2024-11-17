/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_spr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:05:03 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/15 16:42:18 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"
#include "../../minilibx/mlx.h"

void	calculate_draw_borders(t_render render, t_spr_vars *spr_vars)
{
	spr_vars->height = abs((int)(render.sc_height / spr_vars->transform[Y]));
	spr_vars->draw_s[Y] = (-1 * spr_vars->height) / 2 + render.sc_height / 2;
	if (spr_vars->draw_s[Y] < 0)
		spr_vars->draw_s[Y] = 0;
	spr_vars->draw_e[Y] = spr_vars->height / 2 + render.sc_height / 2;
	if (spr_vars->draw_e[Y] >= render.sc_height)
		spr_vars->draw_e[Y] = render.sc_height - 1;
	spr_vars->width = abs((int)(render.sc_height / spr_vars->transform[Y]));
	spr_vars->draw_s[X] = (-1 * spr_vars->width) / 2 + spr_vars->screen_x;
	if (spr_vars->draw_s[X] < 0)
		spr_vars->draw_s[X] = 0;
	spr_vars->draw_e[X] = spr_vars->width / 2 + spr_vars->screen_x;
	if (spr_vars->draw_e[X] >= render.sc_width)
		spr_vars->draw_e[X] = render.sc_width - 1;
}

t_spr_vars	fill_spr(t_vars *vars, t_sprite sprite)
{
	t_spr_vars	spr_vars;
	t_player	player;

	player = vars->player;
	spr_vars.sprite[X] = sprite.spr_pos[X] - (player.pos[X] / TILE_SIZE) + 0.5;
	spr_vars.sprite[Y] = sprite.spr_pos[Y] - (player.pos[Y] / TILE_SIZE) + 0.5;
	spr_vars.inv_det = 1.0 / (player.plane[X] * player.dir[Y] - player.dir[X] \
		* player.plane[Y]);
	spr_vars.transform[X] = spr_vars.inv_det * (player.dir[Y] \
		* spr_vars.sprite[X] - player.dir[X] * spr_vars.sprite[Y]);
	spr_vars.transform[Y] = spr_vars.inv_det * ((-player.plane[Y]) \
		* spr_vars.sprite[X] + player.plane[X] * spr_vars.sprite[Y]);
	spr_vars.screen_x = (int)((vars->render.sc_width / 2) \
		* (1 + (spr_vars.transform[X] / spr_vars.transform[Y])));
	calculate_draw_borders(vars->render, &spr_vars);
	return (spr_vars);
}

int	sprite_display(t_vars *vars, t_sprite *sprite, t_spr_vars spr_vars)
{
	if (sprite->life <= 0)
	{
		vars->game.end_ani = 0;
		sprite->emy_ani = 4;
		if (sprite->spr_ani == 8)
			return (-16777216);
	}
	else if (!sprite->hit && sprite->dist > 7)
		sprite->emy_ani = 0;
	else if (!sprite->hit && sprite->dist <= 1.5f)
		sprite->emy_ani = 1;
	else if (sprite->hit)
	{
		vars->game.end_ani = 0;
		sprite->emy_ani = 3;
	}
	else
		sprite->emy_ani = 2;
	if ((sprite->emy_ani == 0 || sprite->emy_ani == 3)
		&& sprite->spr_ani > 3)
		sprite->spr_ani = 0;
	return (texture_color(&vars->enemy.sprites[sprite->emy_ani] \
		[sprite->spr_ani], spr_vars.tex[X], spr_vars.tex[Y]));
}

void	draw_sprite(t_vars *vars, t_spr_vars spr_vars, t_sprite *sprite,
	double *ddist)
{
	int	pos[3];

	pos[X] = spr_vars.draw_s[X] - 1;
	while (++pos[X] < spr_vars.draw_e[X])
	{
		pos[2] = 64;
		if (sprite->is_enemy)
			pos[2] = 128;
		spr_vars.tex[X] = (int)((pos[X] - ((-1 * spr_vars.width) / 2 \
			+ spr_vars.screen_x)) * pos[2] / spr_vars.width);
		if (spr_vars.transform[Y] > 0 && pos[X] > 0 && pos[X] < \
		vars->render.sc_width && spr_vars.transform[Y] < ddist[pos[X]])
		{
			if (sprite->is_enemy)
				sprite->on_sc = 1;
			advence_p_put(vars, sprite, spr_vars, pos);
		}
	}
}

int	cast_spr(t_vars *vars, double *ddist)
{
	int			i;
	t_sprite	*sprite;
	t_spr_vars	spr_vars;

	sprite = vars->sprites;
	if (!sprite)
		return (0);
	sort_sprites(vars, &sprite);
	if (!sprite)
		return (1);
	i = -1;
	while (++i < vars->game.spr_count)
	{
		if (sprite[i].life <= 0)
			continue ;
		spr_vars = fill_spr(vars, sprite[i]);
		sprite[i].dist = euclid_dist(vars->player.camera, sprite[i].spr_pos);
		if (sprite[i].time == 0 || get_time() - sprite[i].time > 100)
			animation_picker(vars, &sprite[i]);
		draw_sprite(vars, spr_vars, &sprite[i], ddist);
	}
	return (0);
}
