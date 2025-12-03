/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:02:10 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/02 11:38:35 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parsing.h"

bool	texturizing(t_textures *mlx, t_game *g)
{
	g->no_tex = mlx_load_png(mlx->n_texture);
	g->we_tex = mlx_load_png(mlx->w_texture);
	g->ea_tex = mlx_load_png(mlx->e_texture);
	g->so_tex = mlx_load_png(mlx->s_texture);
	if (!g->no_tex || !g->we_tex
		|| !g->ea_tex || !g->so_tex)
	{
		mlx_delete_texture(g->no_tex);
		mlx_delete_texture(g->we_tex);
		mlx_delete_texture(g->ea_tex);
		mlx_delete_texture(g->so_tex);
		return (false);
	}
	return (true);
}

uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	int		i;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	i = (y * tex->width + x) * 4;
	r = tex->pixels[i + 0];
	g = tex->pixels[i + 1];
	b = tex->pixels[i + 2];
	a = tex->pixels[i + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}
