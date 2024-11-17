/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:17:42 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/12 17:18:01 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"
#include "../../minilibx/mlx.h"
#include <math.h>

static int	color(t_vars *vars, int tile_x, int tile_y)
{
	int	max_x;
	int	max_y;

	max_y = double_counter(vars->map) * MAP_TILE;
	if (max_y <= tile_y || tile_y < 0)
		return (rgb_to_hex(0, 0, 0));
	max_x = ft_strlen(vars->map[tile_y / MAP_TILE]) * MAP_TILE;
	if (max_x < tile_x || tile_x < 0 || max_x == 0)
		return (rgb_to_hex(0, 0, 0));
	else if (vars->map[tile_y / MAP_TILE][tile_x / MAP_TILE] == '1'
	|| vars->map[tile_y / MAP_TILE][tile_x / MAP_TILE] == ' '
	|| vars->map[tile_y / MAP_TILE][tile_x / MAP_TILE] == '\0')
		return (rgb_to_hex(0, 0, 0));
	else
		return (rgb_to_hex(255, 255, 255));
}

static void	put_tiles(t_vars *vars, int *pos, double cos_angle,
	double sin_angle)
{
	int	x;
	int	y;
	int	map_size[2];
	int	rotated[2];
	int	center[2];

	map_size[Y] = vars->render.sc_height * 0.20;
	map_size[X] = vars->render.sc_width * 0.20;
	center[X] = pos[X] + map_size[X] / 2;
	center[Y] = pos[Y] + map_size[Y] / 2;
	y = -1;
	while (++y < map_size[Y])
	{
		x = -1;
		while (++x < map_size[X])
		{
			rotated[X] = (x - map_size[X] / 2) * cos_angle
				- (y - map_size[Y] / 2) * sin_angle;
			rotated[Y] = (x - map_size[X] / 2) * sin_angle + (y - map_size[Y]
					/ 2) * cos_angle;
			pixel_put(&vars->ui.mini_map, x, y,
				color(vars, rotated[X] + center[X], rotated[Y] + center[Y]));
		}
	}
}

int	render_mini_map(t_vars *vars)
{
	int		pos[2];
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(nor_angle(vars->player.p_angle + M_PI / 2));
	sin_angle = sin(nor_angle(vars->player.p_angle + M_PI / 2));
	vars->map_h = double_counter(vars->map) * MAP_TILE;
	vars->map_w = find_longest_line(vars->map) * MAP_TILE;
	pos[X] = (vars->player.camera[X] / TILE_SIZE) * MAP_TILE
		- vars->render.sc_width * 0.10;
	pos[Y] = (vars->player.camera[Y] / TILE_SIZE) * MAP_TILE
		- vars->render.sc_height * 0.10;
	put_tiles(vars, pos, cos_angle, sin_angle);
	return (0);
}
