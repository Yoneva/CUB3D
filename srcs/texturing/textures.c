/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 03:58:39 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/29 04:52:00 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/texture.h"
#include "../../includes/parsing.h"

void put_textured_line(t_game *g, int x, t_frame *f)
{
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x;
	int				y;
	double			dist_from_top;
	double			tex_y_ratio;
	int				tex_y;
	uint32_t		color;

	// Choose the correct texture (PNG)
	if (f->ray.is_hit_vert)
	{
		if (f->ray.is_right)
			tex = g->ea_tex;
		else
			tex = g->we_tex;
	}
	else
	{
		if (f->ray.is_up)
			tex = g->no_tex;
		else
			tex = g->so_tex;
	}
	if (!tex)
		return;
	// Determine where on the wall we hit (0.0 - 1.0)
	if (f->ray.is_hit_vert)
		wall_x = f->ray.wall_hit_y;
	else
		wall_x = f->ray.wall_hit_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	// Clamp tex_x
	if (tex_x < 0) 
		tex_x = 0;
	if (tex_x >= (int)tex->width) 
		tex_x = tex->width - 1;

	// Draw the wall column
	y = f->draw_start;
	while (y < f->draw_end)
	{
		dist_from_top = y - (HEIGHT / 2 - f->wall_strip_height / 2);
		tex_y_ratio = dist_from_top / f->wall_strip_height;
		tex_y = (int)(tex_y_ratio * tex->height);
		// Clamp tex_y
		if (tex_y < 0) 
			tex_y = 0;
		if (tex_y >= (int)tex->height) 
			tex_y = tex->height - 1;

		color = get_tex_pixel(tex, tex_x, tex_y);
		(mlx_put_pixel(g->img, x, y, color), y++);
	}
}
