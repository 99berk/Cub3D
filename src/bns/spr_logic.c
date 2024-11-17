/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:54:44 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/13 15:54:49 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"

void	game_logic(t_vars *vars, t_sprite *sprite)
{
	if (sprite->emy_ani == 1 && sprite->dist <= 1)
		vars->player.life -= 25;
	if (sprite->hit)
	{
		sprite->hit = 0;
		if (vars->player.gun_type == 2)
			sprite->life -= 250;
		else if (vars->player.gun_type == 1)
			sprite->life -= 150;
		else
			sprite->life -= 50;
		if (sprite->life <= 0)
		{
			vars->game.enemy_count--;
			if (vars->game.enemy_count == 0)
				vars->d_time = get_time();
		}
	}
	if (vars->player.life <= 0 && !mlx_mouse_show())
		vars->ui.menu = 1;
	if (sprite->life > 0)
		sprite->spr_ani = 0;
	vars->game.end_ani = 1;
}

void	animation_picker(t_vars *vars, t_sprite *sprite)
{
	sprite->time = get_time();
	if (sprite->emy_ani == 0 && sprite->spr_ani < 3)
		sprite->spr_ani++;
	else if (sprite->emy_ani == 1 && sprite->spr_ani < 5)
		sprite->spr_ani++;
	else if (sprite->emy_ani == 2 && sprite->spr_ani < 5)
		sprite->spr_ani++;
	else if (sprite->emy_ani == 3 && sprite->spr_ani < 3)
		sprite->spr_ani++;
	else if (sprite->emy_ani == 4 && sprite->spr_ani < 8)
		sprite->spr_ani++;
	else
		game_logic(vars, sprite);
}
