/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:34:49 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/18 05:20:49 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"


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
		if (configs->texture->flags->C > 0)
			free(configs->texture->ceiling_c);
		if (configs->texture->flags->F > 0)
			free(configs->texture->floor_c);
		if (configs->texture->flags->SO > 0)
			free(configs->texture->s_texture);
		if (configs->texture->flags->WE > 0)
			free(configs->texture->w_texture);
		if (configs->texture->flags->EA > 0)
			free(configs->texture->e_texture);
		if (configs->texture->flags->NO > 0)
			free(configs->texture->n_texture);
	}
}

static char	*remove_spaces(char *input)
{
	int i;
	
	i = 0;
	while (input[i] == ' ')
		i++;
	return(input + i);
}

int	check_lines2(char *input, t_configs *configs)
{
	if (ft_strncmp("EA ", input, 3) == 0)
	{
		if (configs->texture->flags->EA == 0)
			configs->texture->e_texture = ft_strdup(remove_spaces(input + 2));
		configs->texture->flags->EA += 1;
	}
	else if (ft_strncmp("F ", input, 2) == 0)
	{
		if (configs->texture->flags->F == 0)
			configs->texture->floor_c = ft_strdup(remove_spaces(input + 2));
		configs->texture->flags->F += 1;
	}
	else if (ft_strncmp("C ", input, 2) == 0)
	{
		if (configs->texture->flags->C == 0)
			configs->texture->ceiling_c = ft_strdup(remove_spaces(input + 2));
		configs->texture->flags->C += 1;
	}
	else if (ft_strncmp("WE ", input, 3) == 0)
	{
		if (configs->texture->flags->WE == 0)
			configs->texture->w_texture = ft_strdup(remove_spaces(input + 2));	
		configs->texture->flags->WE += 1;
	}
	else
		return (0);
	return (1);
}

int	check_lines(char **info, t_configs *configs, int i)
{
	while(info[++i])
	{
		if (ft_strncmp("NO ", info[i], 3) == 0 )
		{
			if (configs->texture->flags->NO == 0)
				configs->texture->n_texture = ft_strdup(remove_spaces(info[i] + 2));
			configs->texture->flags->NO += 1;
		}
		else if (ft_strncmp("SO ", info[i], 3) == 0)
		{
			if (configs->texture->flags->SO == 0)
				configs->texture->s_texture = ft_strdup(remove_spaces(info[i] + 2));
			configs->texture->flags->SO += 1;
		}
		else
		{
			if (!check_lines2(info[i], configs))
				return (error_message(info, 0), 0);
		}
	}
	if (configs->texture->flags->WE != 1 || configs->texture->flags->SO != 1
		|| configs->texture->flags->NO != 1 || configs->texture->flags->EA != 1 
		|| configs->texture->flags->F != 1 || configs->texture->flags->C != 1)
		return (error_message(info, 0), 0);
	return (free(info), 1);
}

int	parse_texture(t_configs *configs)
{
	int		i;
	int		j;
	char	**info;
	
	i = 0;
	j = 0;
	configs->texture->flags->NO = 0;
	configs->texture->flags->SO = 0;
	configs->texture->flags->WE = 0;
	configs->texture->flags->EA = 0;
	configs->texture->flags->F = 0;
	configs->texture->flags->C = 0;
	info = malloc(7 * sizeof(char *));
	while (configs->file[i] && j < 6)
	{
		if (configs->file[i][0] == '\0')
		{
			i++;
			continue ;
		}
		info[j] = ft_strdup(remove_spaces(configs->file[i]));
		if (count_word(info[j]) != 2)
		{
			freeing(configs, 0);
			error_message(info, 1);
		}
		i++;
		j++;
	}
	info[j] = NULL;
	if (!check_lines(info, configs, -1) || !check_colors(configs))
	{
		perror("unvalide texture");
		freeing(configs, 1);
		exit (0);
	}
	return (i);
}
