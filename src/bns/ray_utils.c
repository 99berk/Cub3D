/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:15:32 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/15 16:42:38 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <math.h>

double	nor_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	fill_variable(t_vars *vars, t_ray *ray)
{
	ray->raydir[X] = cos(vars->render.ray_angle);
	ray->raydir[Y] = sin(vars->render.ray_angle);
	if (!ray->raydir[X])
		ray->raydir[X] += 0.0001f;
	if (!ray->raydir[Y])
		ray->raydir[Y] += 0.0001f;
	ray->delta_dist[X] = fabs(1 / ray->raydir[X]);
	ray->delta_dist[Y] = fabs(1 / ray->raydir[Y]);
	ray->step[X] = 1;
	ray->step[Y] = 1;
	return (0);
}
