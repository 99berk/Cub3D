/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marche.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:41:27 by bakgun            #+#    #+#             */
/*   Updated: 2024/08/15 16:41:38 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../libft/libft.h"
#include "../../includes/bonus.h"

int	set_guns(t_vars *vars)
{
	vars->player.shoot = 0;
	vars->gun_name = ft_calloc(sizeof(char *), 4);
	if (!vars->gun_name)
		return (err("ft_calloc error"));
	vars->gun_name[0] = ft_strdup("./guns/Hunter");
	if (!vars->gun_name[0])
		return (err("ft_calloc error"));
	vars->gun_name[1] = ft_strdup("./guns/Talon");
	if (!vars->gun_name[1])
		return (err("ft_calloc error"));
	vars->gun_name[2] = ft_strdup("./guns/Therm");
	if (!vars->gun_name[2])
		return (err("ft_calloc error"));
	vars->gun_name[3] = NULL;
	vars->player.gun_type = 0;
	vars->ui.ammo = ft_calloc(sizeof(int), 3);
	if (!vars->ui.ammo)
		return (err("ft_calloc error"));
	vars->ui.ammo[0] = 30;
	vars->ui.ammo[1] = 30;
	vars->ui.ammo[2] = 3;
	vars->player.ani_i = 0;
	return (0);
}

int	claim_resources(t_vars *vars)
{
	vars->d_time = get_time();
	if (vars->d_time == 0)
		return (err("Get_time error"));
	vars->ui.sound = ft_calloc(sizeof(char *), 3);
	if (!vars->ui.sound)
		return (err("ft_calloc error"));
	vars->ui.sound[0] = ft_strdup("afplay sounds/menu_track.mp3");
	vars->ui.sound[1] = ft_strdup("afplay sounds/morbid_descent.mp3");
	vars->ui.sound[2] = NULL;
	if (!vars->ui.sound[0] || !vars->ui.sound[1])
		return (err("Strdup error"));
	vars->enemy.filename = ft_calloc(sizeof(char *), 6);
	if (!vars->enemy.filename)
		return (err("ft_calloc error"));
	vars->enemy.filename[0] = ft_strdup("./enemy/idle/idle");
	vars->enemy.filename[1] = ft_strdup("./enemy/attack/attack");
	vars->enemy.filename[2] = ft_strdup("./enemy/walk/walk");
	vars->enemy.filename[3] = ft_strdup("./enemy/damage/damaged");
	vars->enemy.filename[4] = ft_strdup("./enemy/death/death");
	vars->enemy.filename[5] = NULL;
	if (!vars->enemy.filename[0] || !vars->enemy.filename[1]
		|| !vars->enemy.filename[2] || !vars->enemy.filename[3]
		|| !vars->enemy.filename[4])
		return (err("Strdup error"));
	return (0);
}

void	null_canvas(t_vars *vars)
{
	int	i;

	vars->ui.gun_canvas.img = NULL;
	vars->ui.map_arrow.img = NULL;
	vars->ui.mini_map.img = NULL;
	vars->ui.sprites_canvas.img = NULL;
	vars->ui.ui_canvas.img = NULL;
	vars->img.img = NULL;
	i = -1;
	while (++i < 27)
	{
		vars->ui.mars[i].img = NULL;
		if (i < 26)
			vars->ui.alp[i].img = NULL;
		if (i < 2)
			vars->ui.music[i].img = NULL;
		if (i < 10)
			vars->ui.num[i].img = NULL;
		if (i < 4)
			vars->xpm[i].img = NULL;
		if (i < 4)
			vars->ui.healt_bar[i].img = NULL;
	}
}

void	set_default(t_vars *vars)
{
	int	i;

	vars->map = NULL;
	vars->textures.ceiling = NULL;
	vars->textures.floor = NULL;
	i = -1;
	while (++i < 5)
		vars->textures.walls[i] = NULL;
	vars->mlx.mlx = NULL;
	vars->mlx.win = NULL;
	vars->ui.sound = NULL;
	vars->gun = NULL;
	vars->ui.map_arrow.img = NULL;
	vars->enemy.sprites = NULL;
	vars->ui.ammo = NULL;
	vars->gun_name = NULL;
	vars->sprites = NULL;
	vars->render.flag = 0;
	vars->keys.key_a = 0;
	vars->keys.key_s = 0;
	vars->keys.key_d = 0;
	vars->keys.key_w = 0;
	vars->keys.key_la = 0;
	vars->keys.key_ra = 0;
	null_canvas(vars);
}

int	marche(t_vars *vars)
{
	vars->render.sc_height = 900;
	vars->render.sc_width = 1090;
	vars->ui.music_on = 1;
	vars->game.start = 0;
	vars->new_game = 1;
	vars->player.running = 1;
	vars->fov_angle = 60;
	vars->game.spr_count = 0;
	vars->ui.menu = 1;
	vars->player.life = 100;
	vars->player.plane[X] = 0.0;
	vars->player.plane[Y] = 0.60;
	vars->player.fov = vars->fov_angle * (M_PI / 180);
	vars->enemy.index[0] = 4;
	vars->enemy.index[1] = 6;
	vars->enemy.index[2] = 6;
	vars->enemy.index[3] = 4;
	vars->enemy.index[4] = 9;
	set_default(vars);
	if (set_guns(vars) || claim_resources(vars))
		return (1);
	vars->ui.time = get_time();
	if (vars->ui.time == 0)
		return (1);
	return (0);
}