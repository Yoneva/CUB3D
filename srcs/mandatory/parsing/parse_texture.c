/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:34:49 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/01 18:46:31 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	freeing(t_configs *configs, int check)
{
	int	i;

	i = 0;
	while (configs->file[i])
	{
		free(configs->file[i]);
		i++;
	}
	free(configs->file);
	if (check == 1)
	{
		if (configs->texture->ceiling_c)
			free(configs->texture->ceiling_c);
		if (configs->texture->floor_c)
			free(configs->texture->floor_c);
		if (configs->texture->s_texture)
			free(configs->texture->s_texture);
		if (configs->texture->w_texture)
			free(configs->texture->w_texture);
		if (configs->texture->e_texture)
			free(configs->texture->e_texture);
		if (configs->texture->n_texture)
			free(configs->texture->n_texture);
	}
}

char	*rm_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	return (ft_strdup(input + i));
}

char	**fill_texture_array(t_configs *configs, int *i_out)
{
	char	**info;
	int		j;
	int		i;

	i = 0;
	j = 0;
	info = ft_calloc(7, sizeof(char *));
	while (configs->file[i] && j < 6)
	{
		if (configs->file[i][0] == '\0')
		{
			i++;
			continue ;
		}
		info[j] = rm_spaces(configs->file[i]);
		if (count_word(info[j]) != 2)
			return (error_message(info, 1), freeing(configs, 0), NULL);
		i++;
		j++;
	}
	info[j] = NULL;
	*i_out = i;
	return (info);
}

int	parse_texture(t_configs *configs)
{
	int		i;
	int		j;
	char	**info;

	i = 0;
	j = 0;
	configs->texture->flags->no = 0; 
	configs->texture->flags->so = 0;
	configs->texture->flags->we = 0;
	configs->texture->flags->ea = 0;
	configs->texture->flags->f = 0;
	configs->texture->flags->c = 0;
	info = fill_texture_array(configs, &i);
	if (!info)
		return (-1);
	if (!check_lines(info, configs, -1) || !check_colors(configs))
	{
		perror("unvalide texture");
		freeing(configs, 1);
		return (-1);
	}
	return (i);
}
