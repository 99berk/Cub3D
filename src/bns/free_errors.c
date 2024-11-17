/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:41:58 by aaltinto          #+#    #+#             */
/*   Updated: 2024/07/13 02:16:53 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/bonus.h"
#include "../../minilibx/mlx.h"

int	err(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int	free_doubles2(void **str, int size)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (++i < size)
		null_free(str[i]);
	null_free(str);
	return (0);
}

int	free_doubles(char **str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
		null_free(str[i]);
	null_free(str);
	return (0);
}

int	null_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (1);
}
