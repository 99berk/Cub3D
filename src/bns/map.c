/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:05:26 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/12 23:14:31 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"

static int	detect_missing_ind(t_vars *vars)
{
	if (!vars->textures.walls[NO])
		err("North");
	if (!vars->textures.walls[SO])
		err("South");
	if (!vars->textures.walls[WE])
		err("West");
	if (!vars->textures.walls[EA])
		err("East");
	if (!vars->textures.floor)
		err("Floor");
	if (!vars->textures.ceiling)
		err("Ceiling");
	return (1);
}

static int	init(t_vars *vars, char *tmp)
{
	int	ret;

	while (*tmp != '\0')
	{
		if (*tmp != ' ' && *tmp != '\t')
		{
			if (color_init(vars, tmp))
				return (1);
			ret = init_textures(&vars->textures, tmp);
			if (ret == 2)
				break ;
			if (ret == 1)
				return (1);
		}
		tmp++;
	}
	return (0);
}

int	parse_init(t_vars *vars, char *map)
{
	char	**map_tmp;
	char	*tmp;
	char	*tmp2;
	int		i;

	map_tmp = ft_split(map, '\n');
	if (!map_tmp)
		return (err("Split error"));
	i = -1;
	while (map_tmp[++i])
	{
		tmp = ft_strdup(map_tmp[i]);
		if (!tmp)
			return (free_doubles(map_tmp), err("Strdup error"));
		tmp2 = tmp;
		if (init(vars, tmp))
			return (free_doubles(map_tmp), null_free(tmp2), 1);
		null_free(tmp2);
	}
	if (!vars->textures.walls[NO] || !vars->textures.walls[SO]
		|| !vars->textures.walls[WE] || !vars->textures.walls[EA]
		|| !vars->textures.floor || !vars->textures.ceiling)
		return (free_doubles(map_tmp), err("Error! Missing indicators:"),
			detect_missing_ind(vars));
	return (free_doubles(map_tmp), 0);
}
