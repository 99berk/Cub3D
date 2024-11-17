/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:15:43 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/12 23:15:44 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <sys/time.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	texture_color(t_data *data, int x, int y)
{
	int	p_ofset;

	p_ofset = y * data->line_length + x * (data->bits_per_pixel / 8);
	return (*(int *)(data->addr + p_ofset));
}

int	get_color(t_vars *vars, int flag, int x, int y)
{
	vars->render.ray_angle = nor_angle(vars->render.ray_angle);
	if (flag == 0)
	{
		if (vars->render.ray_angle > M_PI / 2
			&& vars->render.ray_angle < 3 * M_PI / 2)
			return (texture_color(&vars->xpm[EA], x, y));
		else
			return (texture_color(&vars->xpm[WE], x, y));
	}
	else
	{
		if (vars->render.ray_angle > 0 && vars->render.ray_angle < M_PI)
			return (texture_color(&vars->xpm[NO], x, y));
		else
			return (texture_color(&vars->xpm[SO], x, y));
	}
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (err("gettimeofday() error"), 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
