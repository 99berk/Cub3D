/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:06:22 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/12 15:06:26 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"
#include "../../minilibx/mlx.h"

int	hover_effect(t_vars *vars, t_data *data, int *pos, t_img_args args)
{
	int	color;
	int	mx;
	int	my;

	mlx_mouse_get_pos(vars->mlx.win, &mx, &my);
	color = texture_color(data, pos[X], pos[Y]);
	if (!vars->ui.menu)
		return (color);
	if (color == 16777215 && my > vars->render.sc_height / 2
		&& my < vars->render.sc_height / 2 + 40 && ((mx < 360 && mx > 40 \
	&& (vars->player.life <= 0 || vars->game.start)) || (mx < 240 && mx > 40))
		&& args.pos_y == 450)
		color = rgb_to_hex(209, 95, 43);
	else if (color == 16777215 && my > vars->render.sc_height / 2 + 80
		&& my < vars->render.sc_height / 2 + 120 && mx < 200 && mx > 40
		&& args.pos_y == 530)
		color = rgb_to_hex(209, 95, 43);
	return (color);
}

void	menu_printer(t_vars *vars, t_data *data, t_data canvas, t_img_args args)
{
	int	color;

	args.pos[Y] = -1;
	while (++args.pos[Y] < args.original_height)
	{
		args.pos[X] = -1;
		while (++args.pos[X] < args.original_width)
		{
			args.tile[Y] = -1;
			while (++args.tile[Y] < args.tile_size)
			{
				args.tile[X] = -1;
				while (++args.tile[X] < args.tile_size)
				{
					color = hover_effect(vars, data, args.pos, args);
					if (color == -16777216)
						continue ;
					pixel_put(&canvas, (args.pos[X] * args.tile_size) \
					+ args.tile[X] + args.pos_x, (args.pos[Y] * args.tile_size)
						+ args.tile[Y] + args.pos_y, color);
				}
			}
		}
	}
}

t_img_args	fill_args(t_vars *vars, char *text, int *pos, double size)
{
	t_img_args	args;

	args.original_height = 8;
	args.original_width = 8;
	args.pos_x = pos[X] - ((ft_strlen(text) * 8 * size) / 2);
	if (args.pos_x < 0)
		args.pos_x = 0;
	if (vars->render.sc_width < args.pos_x + (ft_strlen(text) * size))
		args.pos_x += vars->render.sc_width - (args.pos_x + (ft_strlen(text) \
		* size));
	if (args.pos_x < 0)
		return (err("Error\nText too big to fit"), args.tile_size = 0, args);
	args.pos_y = pos[Y];
	args.tile_size = size;
	return (args);
}

int	print_text(t_vars *vars, char *text, int *pos, double size)
{
	t_img_args	args;
	int			i;
	int			c;

	if (!text)
		return (err("Error\ntext can't be null"));
	args = fill_args(vars, text, pos, size);
	if (args.tile_size == 0)
		return (1);
	i = -1;
	while (text[++i])
	{
		if (text[i] == ' ')
		{
			args.pos_x += 8 * size;
			continue ;
		}
		if (!ft_isalpha(text[i]))
			return (err("Error\nUnrecognized char in the text. All must \
be alphabetical"));
		c = ft_tolower(text[i]) - 97;
		menu_printer(vars, &vars->ui.alp[c], vars->ui.ui_canvas, args);
		args.pos_x += 8 * size;
	}
	return (0);
}
