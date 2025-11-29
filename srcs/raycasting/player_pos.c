/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 04:40:33 by hasbayou          #+#    #+#             */
/*   Updated: 2025/11/25 05:31:37 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"
#include "../../includes/parsing.h"

// rotation matrix :
// x' = x cos(a) - y sin(a)
// y' = x sin(a) + y cos(a)
// plane_len = Vector = (x, y);
// Vector lenght = squareroot(x^2 + y^2);

void	mini_upd(t_game *g, int operator, double mv_type)
{
	double	new_x;
	double	new_y;

	if (operator == 1)
	{
		new_x = g->player.x + g->player.dir_x * mv_type;
		new_y = g->player.y + g->player.dir_y * mv_type;
		if (!has_wall(g->map, new_x, new_y))
		{
			g->player.x = new_x;
			g->player.y = new_y;
		}
	}
	if (operator == -1)
	{
		new_x = g->player.x - g->player.dir_x * mv_type;
		new_y = g->player.y - g->player.dir_y * mv_type;
		if (!has_wall(g->map, new_x, new_y))
		{
			g->player.x = new_x;
			g->player.y = new_y;
		}
	}
}

void	mini_upd_2(t_game *g, int operator, double mv_type)
{
	double	new_x;
	double	new_y;

	if (operator == 1)
	{
		new_x = g->player.x + g->player.plane_x * mv_type;
		new_y = g->player.y + g->player.plane_y * mv_type;
		if (!has_wall(g->map, new_x, new_y))
		{
			g->player.x = new_x;
			g->player.y = new_y;
		}
	}
	if (operator == -1)
	{
		new_x = g->player.x - g->player.plane_x * mv_type;
		new_y = g->player.y - g->player.plane_y * mv_type;
		if (!has_wall(g->map, new_x, new_y))
		{
			g->player.x = new_x;
			g->player.y = new_y;
		}
	}
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dirx;
	double	old_planex;
	double	old_planey;
	double	plane_len;

	old_dirx = player->dir_x;
	old_planex = player->plane_x;
	old_planey = player->plane_y;
	plane_len = sqrt(old_planex * old_planex + old_planey * old_planey);
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dirx * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->dir_y * plane_len;
	player->plane_y = -player->dir_x * plane_len;
}

void	update_player_pos(t_game *g)
{
	t_key	key;

	key = g->player.key;
	if (key.key_up)
		mini_upd(g, 1, MOVE_STEP);
	if (key.key_down)
		mini_upd(g, -1, MOVE_STEP);
	if (key.key_right)
		mini_upd_2(g, -1, MOVE_STEP);
	if (key.key_left)
		mini_upd_2(g, 1, MOVE_STEP);
	if (key.key_turn_right)
		rotate_player(&g->player, ROT_STEP);
	if (key.key_turn_left)
		rotate_player(&g->player, -ROT_STEP);
}
