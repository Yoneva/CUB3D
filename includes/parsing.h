/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:48:24 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/02 12:25:43 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_text_flags
{
	int	c;
	int	f;
	int	ea;
	int	we;
	int	so;
	int	no;
}	t_text_flags;

typedef struct s_textures
{
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	char			*floor_c;
	char			*ceiling_c;
	int				f_color;
	int				c_color;
	t_text_flags	*flags;
}	t_textures;

typedef struct s_configs
{
	t_textures	*texture;
	char		**map;
	int			fd;
	char		**file;
}	t_configs;

//PARSING
char	**get_file(int fd);
int		parse_texture(t_configs *configs);
char	**parse_map(t_configs *configs, char **map);

//PARSING UTILS
void	*ft_realloc(void *str, size_t newsize);
void	error_message(char **arr, int n);
int		count_word(char *input);
void	freeing(t_configs *configs, int check);
char	**normalize_map(char **map, int i, int j);
void	counting(char **map, int *rows, int *max_len);
int		check_colors(t_configs *configs);
char	*rm_spaces(char *input);
int		check_lines(char **info, t_configs *configs, int i);
int		rgb_to_int(int r, int g, int b);

#endif
