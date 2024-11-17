/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:41:58 by aaltinto          #+#    #+#             */
/*   Updated: 2024/09/23 12:11:01 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/cub3d.h"
#include "../../minilibx/mlx.h"

int	err(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int	free_doubles(char **str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (0);
}

int	null_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (1);
}

void	abort_mission(t_vars *vars)
{
	int	i;

	i = -1;
	free_doubles(vars->map);
	null_free(vars->textures.ceiling);
	null_free(vars->textures.floor);
	while (++i < 4)
		null_free(vars->textures.walls[i]);
}

int	close_windows(t_vars *vars)
{
	int	i;

	if (vars->mlx.mlx && vars->mlx.win)
		mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	i = -1;
	while (++i < 4)
		if (vars->xpm[i].img)
			mlx_destroy_image(vars->mlx.mlx, vars->xpm[i].img);
	abort_mission(vars);
	exit(0);
	return (0);
}
