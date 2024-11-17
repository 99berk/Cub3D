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

#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"
#include "../../libft/libft.h"
#include <math.h>

int	count_d(t_vars *vars, char *map)
{
	int	i;

	vars->game.enemy_count = 0;
	vars->game.diamond = 0;
	i = -1;
	while (map[++i])
	{
		if (map[i] == ' ' || map[i] == '\t')
			continue ;
		if (map[i] == 'D')
			vars->game.diamond++;
		else if (map[i] == 'X')
			vars->game.enemy_count++;
	}
	vars->game.diamond_org = vars->game.diamond;
	vars->game.enemy_org = vars->game.enemy_count;
	if (vars->game.diamond == 0)
		return (err("Error: Diamond count must be at least one!"));
	return (0);
}

int	set_enemy(t_vars *vars, t_enemy *enemy, int *len)
{
	int		i;
	int		j;
	char	*filename;

	i = -1;
	enemy->sprites = ft_calloc(sizeof(t_data *), 6);
	if (!enemy->sprites)
		return (err("ft_calloc error"));
	while (++i < 5)
	{
		j = -1;
		enemy->sprites[i] = ft_calloc(sizeof(t_data), enemy->index[i]);
		if (!enemy->sprites[i])
			return (err("ft_calloc error"),
				free_doubles2((void **)enemy->sprites, i));
		while (++j < enemy->index[i])
		{
			filename = get_xpm_filename(enemy->filename[i], j + 1);
			if (!filename || xpm_file_init(vars, &vars->enemy.sprites[i][j],
				filename, len))
				return (null_free(filename), 1);
			null_free(filename);
		}
	}
	return (0);
}

int	get_mars(t_vars *vars, int x, int y)
{
	int		i;
	int		len[2];
	char	*filename;

	i = -1;
	set_len(len, x, y);
	while (++i < 27)
	{
		filename = get_xpm_filename("./mars/mars", i);
		if (!filename || xpm_file_init(vars, &vars->ui.mars[i], filename, len))
			return (null_free(filename), err("Error!"));
		null_free(filename);
	}
	i = -1;
	set_len(len, 380, 97);
	while (++i < 4)
	{
		filename = get_xpm_filename("./health_bar/h", i + 1);
		if (!filename || xpm_file_init(vars, &vars->ui.healt_bar[i], filename,
				len))
			return (null_free(filename), err("Error!"));
		null_free(filename);
	}
	return (0);
}

int	get_textures(t_vars *vars)
{
	int	i;
	int	len[2];

	i = -1;
	if (get_mars(vars, 540, 810))
		return (1);
	set_len(len, 64, 64);
	while (++i < 4)
		if (xpm_file_init(vars, &vars->xpm[i], strip(vars->textures.walls[i]),
				len))
			return (1);
	if (set_len(len, 155, 155), xpm_file_init(vars, &vars->ui.music[0], \
	"./textures/music_on.xpm", len) || xpm_file_init(vars, &vars->ui.music[1],
			"./textures/music_off.xpm", len))
		return (1);
	if (set_len(len, 48, 48), xpm_file_init(vars, &vars->ui.map_arrow,
			"./textures/map_arrow.xpm", len))
		return (1);
	set_len(len, 128, 128);
	set_enemy(vars, &vars->enemy, len);
	vars->sprites = detect_sprites(vars);
	return (!vars->sprites && vars->game.spr_count);
}
