/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 04:29:03 by hasbayou          #+#    #+#             */
/*   Updated: 2025/11/25 07:33:48 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	key_press(mlx_key_data_t keycode, t_key *key)
{
	if (keycode.key == MLX_KEY_W)
		key->key_up = true;
	if (keycode.key == MLX_KEY_S)
		key->key_down = true;
	if (keycode.key == MLX_KEY_A || keycode.key == MLX_KEY_Q)
		key->key_left = true;
	if (keycode.key == MLX_KEY_D)
		key->key_right = true;
	if (keycode.key == MLX_KEY_LEFT)
		key->key_turn_left = true;
	if (keycode.key == MLX_KEY_RIGHT)
		key->key_turn_right = true;
}

void	key_release(mlx_key_data_t keycode, t_key *key)
{
	if (keycode.key == MLX_KEY_W)
		key->key_up = false;
	if (keycode.key == MLX_KEY_S)
		key->key_down = false;
	if (keycode.key == MLX_KEY_A)
		key->key_left = false;
	if (keycode.key == MLX_KEY_D)
		key->key_right = false;
	if (keycode.key == MLX_KEY_LEFT)
		key->key_turn_left = false;
	if (keycode.key == MLX_KEY_RIGHT)
		key->key_turn_right = false;
}

void	init_keys(t_key *key)
{
	key->key_up = false;
	key->key_down = false;
	key->key_left = false;
	key->key_right = false;
	key->key_turn_left = false;
	key->key_turn_right = false;
}

void	keys_event(mlx_key_data_t keycode, void *param)
{
	t_game	*g;
	t_key	key;

	g = (t_game *)param;
	key = g->player.key;
	if (keycode.action == MLX_PRESS)
		key_press(keycode, &key);
	else if (keycode.action == MLX_RELEASE)
		key_release(keycode, &key);
	g->player.key = key;
	if (keycode.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(g->mlx);
		return ;
	}
}
