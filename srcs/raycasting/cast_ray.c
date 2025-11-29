/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 04:47:07 by hasbayou          #+#    #+#             */
/*   Updated: 2025/11/25 05:39:40 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"
#include "../../includes/parsing.h"

void	init_ray_vars(t_ray *ray, double ray_angle)
{
	ray->ray_angle = normalize_angle(ray_angle);
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->is_down = false;
	ray->is_up = false;
	ray->is_right = false;
	ray->is_left = false;
	ray->is_hit_vert = false;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->is_down = true;
	if (!ray->is_down)
		ray->is_up = true;
	if (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
		ray->is_right = true;
	if (!ray->is_right)
		ray->is_left = true;
}

void	vert_or_horz_hit_wall(t_ray *ray, t_horz *horz, t_vert *vert, char type)
{
	if (type == 'v')
	{
		ray->wall_hit_x = vert->vert_hit_x;
		ray->wall_hit_y = vert->vert_hit_y;
		ray->distance = vert->vert_distance;
		ray->is_hit_vert = true;
	}
	else if (type == 'h')
	{
		ray->wall_hit_x = horz->horz_hit_x;
		ray->wall_hit_y = horz->horz_hit_y;
		ray->distance = horz->horz_distance;
		ray->is_hit_horz = true;
	}
}

void	whatiffound(t_horz *horz, t_vert *vert, t_game *g, t_ray *ray)
{
	if (horz->found_horz)
		horz->horz_distance = distance_btw_pts(g->player.x, g->player.y,
				horz->horz_hit_x, horz->horz_hit_y);
	if (vert->found_vert)
		vert->vert_distance = distance_btw_pts(g->player.x, g->player.y,
				vert->vert_hit_x, vert->vert_hit_y);
	if (vert->vert_distance < horz->horz_distance)
		vert_or_horz_hit_wall(ray, horz, vert, 'v');
	else
		vert_or_horz_hit_wall(ray, horz, vert, 'h');
}

t_ray	cast_ray(t_game *g, double ray_angle)
{
	t_ray	ray;
	t_horz	horz;
	t_vert	vert;

	init_ray_vars(&ray, ray_angle);
	g->width = ft_strlen(g->map[0]);
	g->height = how_many_rows(g->map);
	horz.horz_hit_x = 0;
	horz.horz_hit_y = 0;
	horz.found_horz = false;
	horz.y_intercept = floor(g->player.y / TILE_SIZE) * TILE_SIZE;
	horz.horz_distance = INFINITY;
	vert.vert_hit_y = 0;
	vert.vert_distance = INFINITY;
	horizontal_intersection(g, ray, &horz);
	vertical_intersection(g, ray, &vert);
	whatiffound(&horz, &vert, g, &ray);
	return (ray);
}
