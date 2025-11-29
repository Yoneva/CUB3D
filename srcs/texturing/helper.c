/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:02:10 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/27 22:00:12 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/texture.h"
#include "../../includes/parsing.h"

void	texturizing(t_textures *mlx, t_game *g)
{
	g->no_tex = mlx_load_png(mlx->n_texture);
	g->we_tex = mlx_load_png(mlx->w_texture);
	g->ea_tex = mlx_load_png(mlx->e_texture);
	g->so_tex = mlx_load_png(mlx->s_texture);
	if (!g->no_tex || !g->we_tex
		|| !g->ea_tex || !g->so_tex)
	{
		exit(1);
	}
}

uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	int	i;
	
	i = (y * tex->width + x) * 4;
	uint8_t r = tex->pixels[i + 0];
	uint8_t g = tex->pixels[i + 1];
	uint8_t b = tex->pixels[i + 2];
	uint8_t a = tex->pixels[i + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}
