/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:54:06 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/23 06:54:07 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../minilibx/mlx.h"

static int	get_images(t_vars *vars)
{
	vars->xpm[NO].addr = mlx_get_data_addr(vars->xpm[NO].img, \
		&(vars->xpm[NO].bits_per_pixel), &(vars->xpm[NO].line_length), \
		&(vars->xpm[NO].endian));
	if (!vars->xpm[NO].addr)
		return (err("Get data addr error: 'NO'"));
	vars->xpm[SO].addr = mlx_get_data_addr(vars->xpm[SO].img, \
		&(vars->xpm[SO].bits_per_pixel), &(vars->xpm[SO].line_length), \
		&(vars->xpm[SO].endian));
	if (!vars->xpm[SO].addr)
		return (err("Get data addr error: 'SO'"));
	vars->xpm[WE].addr = mlx_get_data_addr(vars->xpm[WE].img, \
		&vars->xpm[WE].bits_per_pixel, &vars->xpm[WE].line_length, \
		&vars->xpm[WE].endian);
	if (!vars->xpm[WE].addr)
		return (err("Get data addr error: 'WE'"));
	vars->xpm[EA].addr = mlx_get_data_addr(vars->xpm[EA].img, \
		&vars->xpm[EA].bits_per_pixel, &vars->xpm[EA].line_length, \
		&vars->xpm[EA].endian);
	if (!vars->xpm[EA].addr)
		return (err("Get data addr error: 'EA'"));
	return (0);
}

int	get_textures(t_vars *vars)
{
	int	x;
	int	y;

	x = 64;
	y = 64;
	vars->xpm[NO].img = (mlx_xpm_file_to_image(vars->mlx.mlx, \
		strip(vars->textures.walls[NO]), &x, &y));
	if (!vars->xpm[NO].img)
		return (err("can't get texture 'NO'"));
	vars->xpm[SO].img = (mlx_xpm_file_to_image(vars->mlx.mlx, \
		strip(vars->textures.walls[SO]), &x, &y));
	if (!vars->xpm[SO].img)
		return (err("can't get texture 'SO'"));
	vars->xpm[WE].img = mlx_xpm_file_to_image(vars->mlx.mlx, \
		strip(vars->textures.walls[WE]), &x, &y);
	if (!vars->xpm[WE].img)
		return (err("can't get texture 'WE'"));
	vars->xpm[EA].img = mlx_xpm_file_to_image(vars->mlx.mlx, \
		strip(vars->textures.walls[EA]), &x, &y);
	if (!vars->xpm[EA].img)
		return (err("can't get texture 'EA'"));
	return (get_images(vars));
}

static void	assign_player(t_vars *vars, int dir)
{
	if (dir == 0)
	{
		vars->player.p_angle = (3 * M_PI) / 2;
		vars->player.camera[X] = vars->player.pos[X];
		vars->player.camera[Y] = vars->player.pos[Y] - 1;
	}
	else if (dir == 1)
	{
		vars->player.p_angle = 0;
		vars->player.camera[X] = vars->player.pos[X] - 1;
		vars->player.camera[Y] = vars->player.pos[Y];
	}
	else if (dir == 2)
	{
		vars->player.p_angle = M_PI / 2;
		vars->player.camera[X] = vars->player.pos[X];
		vars->player.camera[Y] = vars->player.pos[Y] + 1;
	}
	else if (dir == 3)
	{
		vars->player.p_angle = M_PI;
		vars->player.camera[X] = vars->player.pos[X] + 1;
		vars->player.camera[Y] = vars->player.pos[Y];
	}
}

int	detect_player(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (vars->map[++y] != (void *)0)
	{
		x = -1;
		while (vars->map[y][++x])
		{
			vars->player.pos[X] = (x * TILE_SIZE) + TILE_SIZE / 2;
			vars->player.pos[Y] = (y * TILE_SIZE) + TILE_SIZE / 2;
			if (vars->map[y][x] == 'N')
				return (assign_player(vars, 0), 0);
			else if (vars->map[y][x] == 'E')
				return (assign_player(vars, 1), 0);
			else if (vars->map[y][x] == 'S')
				return (assign_player(vars, 2), 0);
			else if (vars->map[y][x] == 'W')
				return (assign_player(vars, 3), 0);
		}
	}
	return (1);
}
