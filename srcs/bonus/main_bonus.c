/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:52:50 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/01 18:47:47 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/raycasting.h"

void	check_input(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (len <= 3)
	{
		write(1, "file is not valid\n", 31);
		exit (1);
	}
	if (str[len - 4] == '/' || str[len - 3] != '.' || str[len - 2] != 'c' 
		|| str[len - 1] != 'u' || str[len] != 'b')
	{
		write(1, "file is not valid\n", 31);
		exit (1);
	}
}

void ll()
{
	system("leaks -q cub3d");
}

int	main(int ac, char **av)
{
	t_configs	configs;
	int			i;

	atexit(ll);
	if (ac != 2)
		return (write(1, "Arguments!!'-'\n", 15), 1);
	check_input(av[1]);
	configs.fd = open(av[1], O_RDONLY);
	if (configs.fd == -1)
		return (perror("Couldn't open the file '-'"), 1);
	configs.texture = malloc(sizeof(t_textures));
	configs.texture->flags = malloc(sizeof(t_text_flags));
	if (!configs.texture || !configs.texture->flags)
		return (perror("malloc"), free(configs.texture->flags)
			, free(configs.texture), 1);
	configs.file = get_file(configs.fd);
	i = parse_texture(&configs);
	if (i < 0)
		return (free(configs.texture), free(configs.texture->flags), 1);
	configs.map = parse_map(&configs, configs.file + i);
	if (!configs.map)
		return (free(configs.texture), free(configs.texture->flags), 1);
	start_game(&configs);
	freeing(&configs, 1);
	(free(configs.texture), free(configs.texture->flags));
	return (0);
}
