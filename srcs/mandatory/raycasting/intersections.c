/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 04:41:06 by hasbayou          #+#    #+#             */
/*   Updated: 2025/12/02 11:38:35 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "parsing.h"

int	has_wall(char **map, double x, double y)
{
	int	tile_x;
	int	tile_y;
	int	map_width;
	int	map_height;

	if (isnan(x) || isnan(y))
		return (1);
	map_width = ft_strlen(map[0]);
	map_height = how_many_rows(map);
	tile_x = (int)floor(x / TILE_SIZE);
	tile_y = (int)floor(y / TILE_SIZE);
	if (tile_y < 0 || tile_y >= map_height || tile_x < 0 || tile_x >= map_width)
		return (1);
	return (map[tile_y][tile_x] == '1');
}

void	is_horz_inter(t_game *g, t_horz *horz, t_ray ray)
{
	double	check_x;
	double	check_y;

	while (horz->next_horz_x >= 0 && horz->next_horz_x <= g->width * TILE_SIZE
		&& horz->next_horz_y >= 0 && horz->next_horz_y <= g->height * TILE_SIZE)
	{
		check_x = horz->next_horz_x;
		if (ray.is_up)
			check_y = horz->next_horz_y + -1e-6;
		else
			check_y = horz->next_horz_y + 1e-6;
		if (has_wall(g->map, check_x, check_y))
		{
			horz->found_horz = true;
			horz->horz_hit_x = horz->next_horz_x;
			horz->horz_hit_y = horz->next_horz_y;
			break ;
		}
		else
		{
			horz->next_horz_x += horz->xstep;
			horz->next_horz_y += horz->ystep;
		}
	}
}

/* y - yplayer = tan(ray_angle) * (x - xplayer) for line equation */

void	horizontal_intersection(t_game *g, t_ray ray, t_horz *horz)
{
	double	tan_a;

	if (ray.is_down)
		horz->y_intercept += TILE_SIZE;
	tan_a = tan(ray.ray_angle);
	if (fabs(tan_a) < 1e-9)
		horz->x_intercept = INFINITY;
	else
		horz->x_intercept = g->player.x
			+ (horz->y_intercept - g->player.y) / tan_a;
	if (ray.is_up)
		horz->ystep = -TILE_SIZE;
	else
		horz->ystep = TILE_SIZE;
	if (fabs(tan_a) < 1e-9)
		horz->xstep = INFINITY;
	else
		horz->xstep = TILE_SIZE / tan_a;
	if (ray.is_left && horz->xstep > 0)
		horz->xstep = -horz->xstep;
	if (ray.is_right && horz->xstep < 0)
		horz->xstep = -horz->xstep;
	horz->next_horz_x = horz->x_intercept;
	horz->next_horz_y = horz->y_intercept;
	is_horz_inter(g, horz, ray);
}

void	is_vert_inter(t_game *g, t_vert *vert, t_ray ray)
{
	double	check_x;
	double	check_y;

	while (vert->next_vert_x >= 0 && vert->next_vert_x <= g->width * TILE_SIZE
		&& vert->next_vert_y >= 0 && vert->next_vert_y <= g->height * TILE_SIZE)
	{
		if (ray.is_left)
			check_x = vert->next_vert_x + -1e-6;
		else
			check_x = vert->next_vert_x + 1e-6;
		check_y = vert->next_vert_y;
		if (has_wall(g->map, check_x, check_y))
		{
			vert->found_vert = true;
			vert->vert_hit_x = vert->next_vert_x;
			vert->vert_hit_y = vert->next_vert_y;
			break ;
		}
		else
		{
			vert->next_vert_x += vert->xstep;
			vert->next_vert_y += vert->ystep;
		}
	}
}

void	vertical_intersection(t_game *g, t_ray ray, t_vert *vert)
{
	double	tan_a;

	vert->vert_hit_y = 0;
	vert->found_vert = false;
	vert->x_intercept = floor(g->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray.is_right)
		vert->x_intercept += TILE_SIZE;
	tan_a = tan(ray.ray_angle);
	vert->y_intercept = g->player.y
		+ (vert->x_intercept - g->player.x) * tan_a;
	if (ray.is_left)
		vert->xstep = -TILE_SIZE;
	else
		vert->xstep = TILE_SIZE;
	if (fabs(tan_a) < 1e-9)
		vert->ystep = INFINITY;
	else
		vert->ystep = TILE_SIZE * tan_a;
	if (ray.is_up && vert->ystep > 0)
		vert->ystep = -vert->ystep;
	if (ray.is_down && vert->ystep < 0)
		vert->ystep = -vert->ystep;
	vert->next_vert_x = vert->x_intercept;
	vert->next_vert_y = vert->y_intercept;
	is_vert_inter(g, vert, ray);
}
