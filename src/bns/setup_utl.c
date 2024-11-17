/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:05:28 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/12 15:05:32 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"

void	set_len(int *arr, int x, int y)
{
	arr[X] = x;
	arr[Y] = y;
}

int	xpm_file_init(t_vars *vars, t_data *data, char *filename, int *len)
{
	data->img = mlx_xpm_file_to_image(vars->mlx.mlx, filename, &len[X],
			&len[Y]);
	if (!data->img)
		return (err("Can't find sprites"));
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (err("Get data addr error"));
	return (0);
}

t_data	*fill_t_data(t_data *data, t_vars *vars, int width, int height)
{
	data->img = mlx_new_image(vars->mlx.mlx, width, height);
	if (!data->img)
		return (err("Img can't initialized"), NULL);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (err("Img addr can't initialized"), NULL);
	return (data);
}

void	destroy_canvases(t_vars *vars)
{
	mlx_destroy_image(vars->mlx.mlx, vars->img.img);
	mlx_destroy_image(vars->mlx.mlx, vars->ui.mini_map.img);
	mlx_destroy_image(vars->mlx.mlx, vars->ui.gun_canvas.img);
	mlx_destroy_image(vars->mlx.mlx, vars->ui.sprites_canvas.img);
	mlx_destroy_image(vars->mlx.mlx, vars->ui.ui_canvas.img);
}

void	make_transparent(t_vars *vars, t_data canvas)
{
	int		x;
	int		y;

	y = -1;
	while (vars->render.sc_height > ++y)
	{
		x = -1;
		while (vars->render.sc_width > ++x)
			pixel_put(&canvas, x, y, -16777216);
	}
}
