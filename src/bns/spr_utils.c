/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:54:54 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/13 15:54:58 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"
#include "../../minilibx/mlx.h"
#include <math.h>

double	euclid_dist(double *cam, double *pos2)
{
	return (sqrt(pow((cam[X] / TILE_SIZE) - pos2[X], 2)
			+ pow((cam[Y] / TILE_SIZE) - pos2[Y], 2)));
}

void	advence_p_put(t_vars *vars, t_sprite *sprite, t_spr_vars spr_vars,
	int *pos)
{
	int	d;
	int	color;

	pos[Y] = spr_vars.draw_s[Y] - 1;
	while (++pos[Y] < spr_vars.draw_e[Y])
	{
		d = (pos[Y]) * 256 - vars->render.sc_height * 128 + spr_vars.height
			* 128;
		spr_vars.tex[Y] = ((d * pos[2]) / spr_vars.height) / 256;
		if (sprite->is_enemy)
			color = sprite_display(vars, sprite, spr_vars);
		else
			color = texture_color(&sprite->sprite, spr_vars.tex[X],
					spr_vars.tex[Y]);
		if (color != -16777216)
			pixel_put(&vars->ui.sprites_canvas, pos[X], pos[Y], color);
	}
}

void	fill_sprites(t_vars *vars, int count)
{
	if (vars->sprites[count].is_enemy)
	{
		vars->sprites[count].spr_pos[X] = vars->sprites[count].org_pos[X];
		vars->sprites[count].spr_pos[Y] = vars->sprites[count].org_pos[Y];
		vars->sprites[count].spr_ani = 0;
		vars->sprites[count].time = 0;
	}
	vars->sprites[count].life = 500;
}

int	texture_fill(t_vars *vars, t_sprite *sprite, char c)
{
	int		x;
	int		y;
	char	*text;

	x = 64;
	y = 64;
	text = choose_texture(c);
	if (!text)
		return (err("Strdup error"));
	sprite->sprite.img = mlx_xpm_file_to_image(vars->mlx.mlx, text, &x, &y);
	if (!sprite->sprite.img)
		return (ft_putstr_fd(text, 2), err(" can't found"), null_free(text));
	sprite->sprite.addr = mlx_get_data_addr(sprite->sprite.img,
			&sprite->sprite.bits_per_pixel, &sprite->sprite.line_length,
			&sprite->sprite.endian);
	if (!sprite->sprite.addr)
		return (null_free(text), err("get_data_addr error"));
	return (null_free(text), 0);
}
