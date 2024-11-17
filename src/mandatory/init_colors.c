/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:47:11 by aaltinto          #+#    #+#             */
/*   Updated: 2024/06/12 16:48:54 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/libft.h"

int	extract_floor_rgb(t_vars *vars)
{
	char	**tmp;
	int		i;

	tmp = ft_split(vars->textures.floor, ',');
	if (!tmp)
		return (err("Split error"));
	if (double_counter(tmp) != 3)
		return (err("Error! Invalid color format"));
	i = -1;
	while (tmp[++i])
	{
		if (ft_atoi(tmp[i]) < 0 || ft_atoi(tmp[i]) > 255)
			return (err("Error! Invalid floor color"));
		vars->textures.floor_rgb[i] = ft_atoi(tmp[i]);
	}
	free_doubles(tmp);
	return (0);
}

int	extract_rgb(t_vars *vars)
{
	char	**tmp;
	int		i;

	tmp = ft_split(vars->textures.ceiling, ',');
	if (!tmp)
		return (err("Split error"));
	if (double_counter(tmp) != 3)
		return (err("Error! Invalid color format"));
	i = -1;
	while (tmp[++i])
	{
		if (ft_atoi(tmp[i]) < 0 || ft_atoi(tmp[i]) > 255)
			return (err("Error! Invalid ceiling color"));
		vars->textures.ceiling_rgb[i] = ft_atoi(tmp[i]);
	}
	free_doubles(tmp);
	return (extract_floor_rgb(vars));
}

int	color_init(t_vars *vars, char *tmp)
{
	if (ft_strnstr(tmp, "F ", 2) != NULL)
	{
		if (vars->textures.floor)
			return (err("Duplicating indicators: 'F'"));
		vars->textures.floor = ft_substr(tmp, 1, ft_strlen(tmp));
		if (!vars->textures.floor)
			return (err("Substr error"));
	}
	else if (ft_strnstr(tmp, "C ", 2) != NULL)
	{
		if (vars->textures.ceiling)
			return (err("Duplicating indicators: 'C'"));
		vars->textures.ceiling = ft_substr(tmp, 1, ft_strlen(tmp));
		if (!vars->textures.ceiling)
			return (err("Substr error"));
	}
	if (vars->textures.ceiling != NULL && vars->textures.floor != NULL
		&& extract_rgb(vars))
		return (1);
	return (0);
}
