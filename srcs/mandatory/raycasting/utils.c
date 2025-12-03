/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 04:43:28 by hasbayou          #+#    #+#             */
/*   Updated: 2025/12/02 17:48:37 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "parsing.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	closing_error(t_game *g)
{
	mlx_close_window(g->mlx);
	free(g);
	printf("%s\n", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

double	normalize_angle(double angle)
{
	double	two_pi;

	two_pi = 2.0 * M_PI;
	angle = fmod(angle, two_pi);
	if (angle < 0)
		angle += two_pi;
	return (angle);
}

int	how_many_rows(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

double	distance_btw_pts(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}
