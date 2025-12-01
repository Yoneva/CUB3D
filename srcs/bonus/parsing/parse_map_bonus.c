/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:38:37 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/01 18:23:08 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

int	max_window(int width, int length)
{
	if (width > 40 || length > 22)
		return (0);
	return (1);
}

int	check_letters(char **map, int i, int j)
{
	int	player;

	player = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E' ||
				map[j][i] == 'W')
				player += 1;
			else if (map[j][i] == '1' || map[j][i] == '0' || map[j][i] == ' ')
			{
				i++;
				continue ;
			}
			else
				return (0);
			i++;
		}
		j++;
	}
	if (player != 1)
		return (0);
	return (1);
}

int	if_walls(char **rect_map, int size, int i, int j)
{
	while (rect_map[i])
	{
		j = 0;
		while (rect_map[i][j])
		{
			if (i == 0 && rect_map[i][j] != '1' && rect_map[i][j] != ' ')
				return (0);
			else if (i == (size - 1) && rect_map[i][j] != '1' &&
				rect_map[i][j] != ' ')
				return (0);
			else if (rect_map[i][j] == '0')
			{
				if (rect_map[i - 1][j] == ' ' || rect_map[i + 1][j] == ' ') 
					return (0);
				else if (rect_map[i][j + 1] == ' ' ||
					rect_map[i][j + 1] == '\0')
					return (0);
				else if (rect_map[i][j - 1] == ' ' || j == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**parse_map(t_configs *configs, char **file)
{
	int		i;
	char	**map;
	int		max_len;
	int		size ;
	char	**rect_map;

	i = 0;
	size = 0;
	max_len = 0;
	while (file[i][0] == '\0')
		i++;
	map = file + i;
	counting(map, &size, &max_len);
	rect_map = normalize_map(map, max_len, size);
	if (!check_letters(map, 0, 0) || !if_walls(rect_map, size, 0, 0) 
		|| !max_window(max_len, size))
	{
		perror("unvalid map");
		return (freeing(configs, 1), error_message(rect_map, 0), NULL);
	}
	error_message(rect_map, 0);
	return (map);
}
