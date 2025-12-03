/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:58:37 by hasbayou          #+#    #+#             */
/*   Updated: 2025/12/03 15:31:37 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "texture.h"

void	position(t_player *player, int dirx, int diry)
{
	player->dir_x = dirx;
	player->dir_y = diry;
}

void	handle_directions(t_player *player, char **map, int r)
{
	int	c;

	c = 0;
	while (map[r][c])
	{
		if (map[r][c] == 'N' || map[r][c] == 'W' || map[r][c] == 'S'
			|| map[r][c] == 'E')
		{
			if (map[r][c] == 'N')
				position(player, 0, -1);
			if (map[r][c] == 'S')
				position(player, 0, 1);
			if (map[r][c] == 'E')
				position(player, 1, 0);
			if (map[r][c] == 'W')
				position(player, -1, 0);
			player->x = (double)c * TILE_SIZE + TILE_SIZE * 0.5;
			player->y = (double)r * TILE_SIZE + TILE_SIZE * 0.5;
			player->plane_x = player->dir_y * FOV_FACTOR;
			player->plane_y = -player->dir_x * FOV_FACTOR;
			map[r][c] = '0';
		}
		c++;
	}
}

void	put_player_in_map(t_player *player, char **map)
{
	int		r;

	r = 0;
	while (map[r])
	{
		handle_directions(player, map, r);
		r++;
	}
}

int	init_everything(t_game *g, t_configs *configs)
{
	int		rows;
	int		cols;
	char	**rect;

	rows = 0;
	cols = 0;
	counting(configs->map, &rows, &cols);
	rect = normalize_map(configs->map, cols, rows);
	if (!rect)
	{
		free(g);
		return (0);
	}
	g->map = rect;
	g->c_col = configs->texture->c_color;
	g->f_col = configs->texture->f_color;
	g->player.x = (double)WIDTH / 2;
	g->player.y = (double)HEIGHT / 2;
	put_player_in_map(&g->player, g->map);
	return (1);
}

void	start_game(t_configs *configs)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		return ;
	g->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!g->mlx)
		(free(g), printf("%s\n", mlx_strerror(mlx_errno)), exit(EXIT_FAILURE));
	if (!texturizing(configs->texture, g))
		return (closing_error(g));
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img)
		closing_error(g);
	if (mlx_image_to_window(g->mlx, g->img, 0, 0) == -1)
		closing_error(g);
	if (!init_everything(g, configs))
		closing_error(g);
	(init_keys(&g->player.key), mlx_key_hook(g->mlx, keys_event, g));
	(mlx_loop_hook(g->mlx, draw_frame, g), mlx_loop(g->mlx));
	(mlx_delete_texture(g->no_tex), mlx_delete_texture(g->we_tex));
	(mlx_delete_texture(g->ea_tex), mlx_delete_texture(g->so_tex));
	(mlx_delete_image(g->mlx, g->img), mlx_terminate(g->mlx));
	(free_map(g->map), free(g));
}
