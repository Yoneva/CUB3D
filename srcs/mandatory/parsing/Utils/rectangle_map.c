/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:09:25 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/02 11:38:06 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	counting(char **map, int *rows, int *max_len)
{
	int	len;

	while (map[*rows])
	{
		len = ft_strlen(map[*rows]);
		if (len > *max_len)
			*max_len = len;
		(*rows)++;
	}
}

char	**normalize_map(char **map, int max_len, int rows)
{
	int		i;
	int		j;
	int		len;
	char	**new_map;

	i = 0;
	j = 0;
	new_map = malloc((rows + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		new_map[i] = malloc(max_len + 1);
		if (!new_map[i])
			return (error_message(new_map, 0), NULL);
		ft_strlcpy(new_map[i], map[i], max_len + 1);
		j = len;
		while (j++ < max_len)
			new_map[i][j] = ' ';
		new_map[i][max_len] = '\0';
		i++;
	}
	new_map[rows] = 0;
	return (new_map);
}
