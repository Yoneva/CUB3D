/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 04:38:19 by hasbayou          #+#    #+#             */
/*   Updated: 2025/12/02 13:03:52 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "texture.h"

void	just_drawing_alittle(t_game *g)
{
	int	xx;
	int	yy;

	yy = 0;
	while (yy < HEIGHT)
	{
		xx = 0;
		while (xx < WIDTH)
		{
			if (yy < HEIGHT / 2)
				mlx_put_pixel(g->img, xx, yy, (uint32_t)g->c_col);
			else
				mlx_put_pixel(g->img, xx, yy, (uint32_t)g->f_col);
			xx++;
		}
		yy++;
	}
}

void	fill_frame(t_game *g, t_frame *frame)
{
	frame->player_angle = atan2(g->player.dir_y, g->player.dir_x);
	frame->half_fov = FOV_ANGLE / 2.0;
	frame->ray_angle = frame->player_angle - frame->half_fov;
	frame->distance_proj_plane = (WIDTH / 2.0) / tan(frame->half_fov);
}

/*	tan(half_fov) = (width / 2) / distance proj plane ; (tan = opp / adj)
	adj = distance proj plane
	distance proj plane = (width / 2) / tan(half_fov) */

void	draw_frame(void *param)
{
	t_game	*g;
	t_frame	frame;
	int		col;

	g = (t_game *)param;
	(update_player_pos(g), just_drawing_alittle(g), fill_frame(g, &frame));
	col = 0;
	while (col < WIDTH)
	{
		frame.curr_angle = normalize_angle(frame.ray_angle
				+ (double)col * (FOV_ANGLE / (double)WIDTH));
		frame.ray = cast_ray(g, frame.curr_angle);
		frame.corr_dist = frame.ray.distance
			* cos(normalize_angle(frame.curr_angle - frame.player_angle));
		frame.wall_strip_height = (TILE_SIZE / frame.corr_dist)
			* frame.distance_proj_plane;
		frame.draw_start = -(int)frame.wall_strip_height / 2 + HEIGHT / 2;
		frame.draw_end = (int)frame.wall_strip_height / 2 + HEIGHT / 2;
		if (frame.draw_start < 0)
			frame.draw_start = 0;
		if (frame.draw_end >= HEIGHT)
			frame.draw_end = HEIGHT - 1;
		(put_textured_line(g, col, &frame, 0), col++);
	}
}
