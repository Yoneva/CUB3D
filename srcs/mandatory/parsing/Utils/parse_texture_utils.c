/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:41:25 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/02 12:30:40 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rgb_to_int(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

bool	check_coma(char *str)
{
	int	i;
	int	coma;

	i = 0;
	coma = 0;
	while (str[i])
	{
		if (str[i] == ',')
			coma++;
		i++;
	}
	if (coma != 2)
		return (false);
	return (true);
}

static int	convert_rgb(char *str)
{
	char	**parts;
	int		r;
	int		g;
	int		b;
	int		color;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (-1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	color = rgb_to_int(r, g, b);
	error_message(parts, 0);
	return (color);
}

int	check_colors(t_configs *configs)
{
	if (!check_coma(configs->texture->ceiling_c) 
		|| !check_coma(configs->texture->floor_c))
		return (0);
	configs->texture->c_color = convert_rgb(configs->texture->ceiling_c);
	configs->texture->f_color = convert_rgb(configs->texture->floor_c);
	if (configs->texture->c_color == -1 || configs->texture->f_color == -1)
		return (0);
	return (1);
}
