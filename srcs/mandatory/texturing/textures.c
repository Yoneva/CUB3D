/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 03:58:39 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/01 10:56:40 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parsing.h"

//chose what texture is needed
mlx_texture_t	*w_texture(t_frame *f, t_game *g)
{
	mlx_texture_t	*tex;

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
		return (NULL);
	return (tex);
}

//floor removes decimal part
int	w_coordinate(t_frame *f, mlx_texture_t *t)
{
	double	wall_x;
	int		tex_x;

	if (f->ray.is_hit_vert)
		wall_x = f->ray.wall_hit_y;
	else
		wall_x = f->ray.wall_hit_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * t->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)t->width)
		tex_x = t->width - 1;
	return (tex_x);
}

void	put_textured_line(t_game *g, int x, t_frame *f, int y)
{
	mlx_texture_t	*tex;
	double			dist_from_top;
	double			tex_y_ratio;
	int				tex_y;
	uint32_t		color;

	y = f->draw_start;
	tex = w_texture(f, g);
	if (!tex)
		return ;
	g->tex_x = w_coordinate(f, tex);
	while (y < f->draw_end)
	{
		dist_from_top = y - ((double)HEIGHT / 2 - f->wall_strip_height / 2);
		tex_y_ratio = dist_from_top / f->wall_strip_height;
		tex_y = (int)(tex_y_ratio * tex->height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		color = get_tex_pixel(tex, g->tex_x, tex_y);
		(mlx_put_pixel(g->img, x, y, color), y++);
	}
}
