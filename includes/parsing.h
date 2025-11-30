#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/Libft/libft.h"
# include "../libs/Libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_text_flags {
	int	C;
	int	F;
	int	EA;
	int	WE;
	int	SO;
	int	NO;
} t_text_flags;

typedef struct s_textures {
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char		*floor_c;
	char		*ceiling_c;
	int			f_color;
	int			c_color;
	t_text_flags *flags;
} t_textures;

typedef struct s_configs {
	t_textures	*texture;
	char		**map;
	int			fd;
	char		**file;
} t_configs;

//PARSING
char	**get_file(int fd);
int		parse_texture(t_configs *configs);
char	**parse_map(t_configs *configs, char **map);

//PARSING UTILS
void		*ft_realloc(void *str, size_t newsize);
void		error_message(char **arr, int n);
int			count_word(char *input);
void		freeing(t_configs *configs, int check);
char		**normalize_map(char **map, int i, int j);
void		counting(char **map, int *rows, int *max_len);
int			check_colors(t_configs *configs);
char	*rm_spaces(char *input);
int			check_lines(char **info, t_configs *configs, int i);

#endif
