/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:38:25 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/13 13:38:28 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"
#include <signal.h>
#include <stdlib.h>

void	abort_mission(t_vars *vars, int close, int child)
{
	null_free(vars->textures.ceiling);
	null_free(vars->textures.floor);
	null_free(vars->textures.walls[0]);
	null_free(vars->textures.walls[1]);
	null_free(vars->textures.walls[2]);
	null_free(vars->textures.walls[3]);
	null_free(vars->sprites);
	if (close)
		free_doubles(vars->map);
	free_doubles2((void **)vars->gun_name, 3);
	free_doubles2((void **)vars->ui.sound, 3);
	free_doubles2((void **)vars->enemy.filename, 5);
	null_free(vars->ui.ammo);
	(void)child;
}

int	free_stuff(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		if (vars->ui.healt_bar[i].img)
			mlx_destroy_image(vars->mlx.mlx, vars->ui.healt_bar[i].img);
		if (vars->xpm[i].img)
			mlx_destroy_image(vars->mlx.mlx, vars->xpm[i].img);
	}
	i = -1;
	while (++i < vars->game.spr_count)
		if (vars->sprites[i].sprite.img)
			mlx_destroy_image(vars->mlx.mlx, vars->sprites[i].sprite.img);
	i = -1;
	while (vars->enemy.sprites && ++i < 5)
	{
		j = -1;
		while (++j < vars->enemy.index[i])
			if (vars->enemy.sprites[i][j].img)
				mlx_destroy_image(vars->mlx.mlx, vars->enemy.sprites[i][j].img);
		null_free(vars->enemy.sprites[i]);
	}
	return (null_free(vars->enemy.sprites));
}

int	free_gun(t_vars *vars)
{
	int	i;
	int	j;
	int	det;

	i = -1;
	while (vars->gun && ++i < 3 && !det)
	{
		j = -1;
		while (++j < 15 && !det)
		{
			if (vars->gun[i][j].img == NULL || !vars->gun[i])
			{
				det = 1;
				break ;
			}
			if (i != 1 && j > 9)
				break ;
			mlx_destroy_image(vars->mlx.mlx, vars->gun[i][j].img);
		}
	}
	return (free_doubles2((void **)vars->gun, 3));
}

int	close_windows(t_vars *vars, int close, int child)
{
	if (!child)
	{
		kill(vars->game.pid + 1, SIGKILL);
		sleep(1);
	}
	if (vars->ui.map_arrow.img)
		mlx_destroy_image(vars->mlx.mlx, vars->ui.map_arrow.img);
	free_gun(vars);
	free_stuff(vars);
	abort_mission(vars, close, child);
	mlx_destroy_window(vars->mlx.mlx, vars->mlx.win);
	if (!close)
		return (0);
	system("leaks cub3d");
	return (exit(0), 0);
}
