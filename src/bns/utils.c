/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:42:18 by aaltinto          #+#    #+#             */
/*   Updated: 2024/06/25 15:55:51 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../libft/libft.h"

int	is_space(int c)
{
	return (c == 32);
}

char	*strip(char *str)
{
	char	*end;

	if (!str)
		return (err("string is null"), NULL);
	while (is_space((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && is_space((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

int	double_counter(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	find_longest_line(char **str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while ((str)[++i])
		if (len < (int)ft_strlen((str)[i]))
			len = ft_strlen((str)[i]);
	return (len);
}

char	**reallocate_double(char **str)
{
	char	**tmp;
	int		i;
	int		j;
	int		len;

	len = find_longest_line(str);
	tmp = (char **)ft_calloc(sizeof(char *), (double_counter(str) + 1));
	if (!tmp)
		return (err("ft_calloc error"), NULL);
	i = -1;
	while ((str)[++i])
	{
		tmp[i] = ft_calloc(sizeof(char), len + 1);
		if (!tmp[i])
			return (free_doubles(tmp), err("ft_calloc error"), NULL);
		j = -1;
		while ((str)[i][++j])
			tmp[i][j] = (str)[i][j];
		tmp[i][j] = '\0';
	}
	tmp[i] = NULL;
	return (tmp);
}
