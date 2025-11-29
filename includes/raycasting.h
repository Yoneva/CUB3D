/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 03:25:38 by hasbayou          #+#    #+#             */
/*   Updated: 2025/11/29 09:18:25 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "parsing.h"

# define WIDTH 800
# define HEIGHT 600
# define FOV_FACTOR 0.66
# define TILE_SIZE 	1.0
# define FOV_ANGLE (60.0 * M_PI / 180.0)
# define MOVE_STEP 0.08
# define ROT_STEP 0.04

typedef struct s_key {
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	key_turn_left;
	bool	key_turn_right;
}			t_key;

typedef struct s_player {
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	t_key	key;
} t_player;

typedef struct s_ray {
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	bool	is_hit_vert;
	bool	is_hit_horz;
	bool	is_up;
	bool	is_down;
	bool	is_left;
	bool	is_right;
	int		width;
	int		height;
}			t_ray;

typedef struct s_game {
	mlx_t		*mlx;
	mlx_image_t	*img;
	char 		**map;
	int			width;
	int			height;
	t_player	player;
	t_ray		ray;
	int			tex_x;
	mlx_texture_t *no_tex;
	mlx_texture_t *so_tex;
	mlx_texture_t *we_tex;
	mlx_texture_t *ea_tex;
} t_game;

typedef struct	s_horz {
	bool	found_horz;
	double	horz_hit_x;
	double	horz_hit_y;
	double	next_horz_x;
	double	next_horz_y;
	double	y_intercept;
	double	x_intercept;
	double	ystep;
	double	xstep;
	double	horz_distance;
}				t_horz;

typedef struct	s_vert {
	bool	found_vert;
	double	vert_hit_x;
	double	vert_hit_y;
	double	next_vert_x;
	double	next_vert_y;
	double	y_intercept;
	double	x_intercept;
	double	ystep;
	double	xstep;
	double	vert_distance;
}				t_vert;

typedef struct	s_frame {
	double	player_angle;
	double	half_fov;
	double	ray_angle;
	double	curr_angle;
	double	distance_proj_plane;
	double	corr_dist;
	double	wall_strip_height;
	int		draw_start;
	int		draw_end;
	uint32_t color;
	t_ray	ray;
}			t_frame;

typedef struct	s_map {
	int			rows;
	int			cols;
	int			tile;
	int			px;
	int			py;
	uint32_t	color;
}				t_map;

void    start_game(t_configs *configs);

void	init_keys(t_key *key);
void	keys_event(mlx_key_data_t keycode, void *param);

void	draw_frame(void *param);
void	mini_map(t_game *g);

t_ray	cast_ray(t_game *g, double ray_angle);
void	update_player_pos(t_game *g);

void	horizontal_intersection(t_game *g, t_ray ray, t_horz *horz);
void	vertical_intersection(t_game *g, t_ray ray, t_vert *vert);
int		has_wall(char **map, double x, double y);

int		how_many_rows(char **map);
double	normalize_angle(double angle);
double	distance_btw_pts(double x1, double y1, double x2, double y2);
void	closing_error(t_game *g);

void	free_map(char **map);

#endif
