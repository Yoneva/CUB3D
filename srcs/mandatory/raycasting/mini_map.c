/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 05:37:15 by hasbayou          #+#    #+#             */
/*   Updated: 2025/11/27 05:46:44 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"
#include "../../includes/parsing.h"

void	draw_map(t_game *g, t_map *map, int i)
{
	int	x;
	int	y;
	int	j;

	j = 0;
	while (j < map->cols)
	{
		if (g->map[i][j] == '1')
			map->color = 0xFFB6C1FF;
		else
			map->color = 0x00000000;
		map->px = 10 + j * map->tile;
		map->py = 10 + i * map->tile;
		y = 0;
		while (y < map->tile)
		{
			x = 0;
			while (x < map->tile)
				(mlx_put_pixel(g->img, map->px + x, map->py + y,
						map->color), x++);
			y++;
		}
		j++;
	}
}

void	player_in_mini_map(t_game *g, t_map *map)
{
	int	ppx;
	int	ppy;
	int	i;
	int	j;

	ppx = 8 + (int)(g->player.x * map->tile);
	ppy = 8 + (int)(g->player.y * map->tile);
	i = -1;
	while (i <= 2)
	{
		j = -1;
		while (j <= 2)
			(mlx_put_pixel(g->img, ppx + i, ppy + j, 0xFF66BEFF), j++);
		i++;
	}
}

void	mini_map(t_game *g)
{
	t_map		map;
	int			i;

	map.rows = how_many_rows(g->map);
	map.cols = ft_strlen(g->map[0]);
	map.tile = 6;
	i = 0;
	while (i < map.rows)
	{
		draw_map(g, &map, i);
		i++;
	}
	player_in_mini_map(g, &map);
}
