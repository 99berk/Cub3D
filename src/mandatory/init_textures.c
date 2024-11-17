/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:50:09 by aaltinto          #+#    #+#             */
/*   Updated: 2024/06/12 16:49:39 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/libft.h"
#include "../../minilibx/mlx.h"

int	get_walls(t_textures *textures, char *tmp, int dir)
{
	if (dir == 0 && !textures->walls[NO])
		textures->walls[NO] = ft_substr(tmp, 2, ft_strlen(tmp));
	else if (dir == 1 && !textures->walls[SO])
		textures->walls[SO] = ft_substr(tmp, 2, ft_strlen(tmp));
	else if (dir == 2 && !textures->walls[WE])
		textures->walls[WE] = ft_substr(tmp, 2, ft_strlen(tmp));
	else if (dir == 3 && !textures->walls[EA])
		textures->walls[EA] = ft_substr(tmp, 2, ft_strlen(tmp));
	else
		return (err("Error!\nDuplicating wall textures"));
	if (!textures->walls[dir])
		return (err("Substr error!"));
	return (0);
}

int	init_textures(t_textures *textures, char *tmp)
{
	int	ret;

	ret = -1;
	if (ft_strnstr(tmp, "NO ", 3) != NULL)
		ret = get_walls(textures, tmp, NO);
	else if (ft_strnstr(tmp, "SO ", 3) != NULL)
		ret = get_walls(textures, tmp, SO);
	else if (ft_strnstr(tmp, "WE ", 3) != NULL)
		ret = get_walls(textures, tmp, WE);
	else if (ft_strnstr(tmp, "EA ", 3) != NULL)
		ret = get_walls(textures, tmp, EA);
	if (ret == 0 || (*tmp == 'F' && (*(tmp + 1)) == ' ') || (*tmp == 'C'
			&& (*(tmp + 1)) == ' ') || *tmp == '0' || *tmp == '1')
		return (2);
	if (ret == 1)
		return (1);
	return (err("Invalid character: "), err(tmp), 1);
}
