/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:05:03 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/15 16:41:59 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"
#include <math.h>
#include <stdlib.h>

int	find_side_dist(t_vars *vars, t_ray *ray)
{
	double	map_x;
	double	map_y;

	map_x = vars->player.camera[X] / TILE_SIZE;
	map_y = vars->player.camera[Y] / TILE_SIZE;
	if (ray->raydir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = (map_x - (int)map_x) * ray->delta_dist[X];
	}
	else
		ray->side_dist[X] = ((int)map_x + 1.0 - map_x) * ray->delta_dist[X];
	if (ray->raydir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = (map_y - (int)map_y) * ray->delta_dist[Y];
	}
	else
		ray->side_dist[Y] = ((int)map_y + 1.0 - map_y) * ray->delta_dist[Y];
	return (0);
}

int	check_hit(t_vars *vars, t_ray *ray)
{
	int	map_grid[2];

	map_grid[X] = (int)(vars->player.camera[X] / TILE_SIZE);
	map_grid[Y] = (int)(vars->player.camera[Y] / TILE_SIZE);
	while (vars->map[map_grid[Y]][map_grid[X]] != '1')
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			map_grid[X] += ray->step[X];
			vars->render.flag = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			map_grid[Y] += ray->step[Y];
			vars->render.flag = 1;
		}
	}
	return (0);
}

int	calc_texture(t_vars *vars, t_ray *ray, double dist)
{
	double	wall_x;
	int		tex_x;
	int		tex_width;

	tex_width = 64;
	if (vars->render.flag == 0)
		wall_x = vars->player.camera[Y] / TILE_SIZE + (dist / \
		cos(vars->render.ray_angle - vars->player.p_angle)) * ray->raydir[Y];
	else
		wall_x = vars->player.camera[X] / TILE_SIZE + (dist / \
		cos(vars->render.ray_angle - vars->player.p_angle)) * ray->raydir[X];
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)tex_width);
	if (vars->render.flag == 0 && ray->raydir[X] > 0)
		tex_x = tex_width - tex_x - 1;
	if (vars->render.flag == 1 && ray->raydir[Y] < 0)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	print_wall(t_vars *vars, double dist, int ray, t_ray *ray_data)
{
	int		wall_height;
	int		pix[2];
	int		tex[2];
	double	step;
	double	tex_pos;

	if (dist == 0.0f)
		dist += 0.000001f;
	wall_height = (int)(vars->render.sc_height / dist);
	pix[TOP] = -wall_height / 2 + vars->render.sc_height / 2;
	if (pix[TOP] < 0)
		pix[TOP] = 0;
	pix[BOT] = wall_height / 2 + vars->render.sc_height / 2;
	if (pix[BOT] > vars->render.sc_height)
		pix[BOT] = vars->render.sc_height;
	tex[X] = calc_texture(vars, ray_data, dist);
	step = (double)64 / wall_height;
	tex_pos = (pix[TOP] - vars->render.sc_height / 2 + wall_height / 2) * step;
	while (pix[TOP] < pix[BOT])
	{
		tex[Y] = (int)tex_pos % 64;
		tex_pos += step;
		pixel_put(&vars->img, ray, pix[TOP]++,
			get_color(vars, vars->render.flag, tex[X], tex[Y]));
	}
}

int	cast_rays(t_vars *vars, int ray)
{
	t_ray	ray_data;
	double	*wall_dist;

	wall_dist = (double *)ft_calloc(sizeof(double), vars->render.sc_width);
	if (!wall_dist)
		return (err("ft_calloc error"));
	vars->render.ray_angle = vars->player.p_angle - (vars->player.fov / 2);
	while (++ray < vars->render.sc_width)
	{
		if (fill_variable(vars, &ray_data) || find_side_dist(vars, &ray_data)
			|| check_hit(vars, &ray_data))
			return (null_free(wall_dist), -1);
		if (vars->render.flag == 0)
			wall_dist[ray] = ray_data.side_dist[X] - ray_data.delta_dist[X];
		else
			wall_dist[ray] = ray_data.side_dist[Y] - ray_data.delta_dist[Y];
		if (wall_dist[ray] < 0)
			return (null_free(wall_dist));
		wall_dist[ray] *= cos(vars->render.ray_angle - vars->player.p_angle);
		print_wall(vars, wall_dist[ray], ray, &ray_data);
		vars->render.ray_angle += vars->player.fov / vars->render.sc_width;
	}
	if (vars->game.spr_count && cast_spr(vars, wall_dist))
		return (null_free(wall_dist), err("Cast sprites error"));
	return (null_free(wall_dist), 0);
}
