/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 02:18:40 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/29 09:17:51 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "raycasting.h"

//TEXTURES
void	texturizing(t_textures *mlx, t_game *texture);
void	    put_textured_line(t_game *g, int x, t_frame *f, int y);
uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y);

#endif