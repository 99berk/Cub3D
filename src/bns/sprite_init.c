/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:37:48 by aaltinto          #+#    #+#             */
/*   Updated: 2024/08/13 13:37:49 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"

int	sort_sprites(t_vars *vars, t_sprite **sprites)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < vars->game.spr_count - 1)
	{
		j = 0;
		while (j < vars->game.spr_count - i - 1)
		{
			if (euclid_dist(vars->player.pos, (*sprites)[j].spr_pos)
				< euclid_dist(vars->player.pos, (*sprites)[j + 1].spr_pos))
			{
				tmp = (*sprites)[j];
				(*sprites)[j] = (*sprites)[j + 1];
				(*sprites)[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*choose_texture(char c)
{
	char	*text;

	if (c == 'X')
		text = ft_strdup("./textures/barrel.xpm");
	if (c == 'B')
		text = ft_strdup("./textures/barrel.xpm");
	if (c == 'D')
		text = ft_strdup("./textures/collectible_img.xpm");
	return (text);
}

int	assign_sprites(t_vars *vars, t_sprite *sprites, int x, int y)
{
	sprites->spr_pos[X] = (double)x;
	sprites->spr_pos[Y] = (double)y;
	sprites->org_pos[X] = (double)x;
	sprites->org_pos[Y] = (double)y;
	if (vars->map[y][x] == 'X')
		sprites->is_enemy = 1;
	else
		sprites->is_enemy = 0;
	sprites->hit = 0;
	sprites->on_sc = 0;
	sprites->life = 500;
	sprites->emy_ani = 0;
	sprites->spr_ani = 0;
	sprites->time = 0;
	if (vars->map[y][x] == 'D')
		sprites->is_diamond = 1;
	else
		sprites->is_diamond = 0;
	if (texture_fill(vars, sprites, vars->map[y][x]))
		return (1);
	return (0);
}

t_sprite	*count_sprites(t_vars *vars)
{
	int			count;
	int			x;
	int			y;
	t_sprite	*sprites;

	count = 0;
	y = -1;
	while (vars->map[++y] != NULL)
	{
		x = -1;
		while (vars->map[y][++x] != '\0')
			if (vars->map[y][x] == 'X' || vars->map[y][x] == 'B'
				|| vars->map[y][x] == 'D')
				count++;
	}
	if (count == 0)
		return (NULL);
	vars->game.spr_count = count;
	sprites = ft_calloc(sizeof(t_sprite), (count));
	if (!sprites)
		return (err("ft_calloc error"), NULL);
	return (sprites);
}

t_sprite	*detect_sprites(t_vars *vars)
{
	int			count;
	int			x;
	int			y;
	t_sprite	*sprites;

	sprites = count_sprites(vars);
	count = vars->game.spr_count;
	if (!sprites)
		return (err("ft_calloc error"), NULL);
	y = -1;
	while (vars->map[++y] != NULL)
	{
		x = -1;
		while (vars->map[y][++x] != '\0')
		{
			if (vars->map[y][x] != 'X' && vars->map[y][x] != 'D'
				&& vars->map[y][x] != 'B')
				continue ;
			count--;
			assign_sprites(vars, &sprites[count], x, y);
		}
		if (count == -1)
			break ;
	}
	return (sort_sprites(vars, &sprites), sprites);
}
