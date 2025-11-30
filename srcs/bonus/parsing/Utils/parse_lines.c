/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:52:28 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/30 17:08:16 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/parsing.h"

int	check_lines3(char *input, t_configs *configs)
{
	if (ft_strncmp("C ", input, 2) == 0)
	{
		if (configs->texture->flags->C == 0)
			configs->texture->ceiling_c = ft_strdup(rm_spaces(input + 2));
		configs->texture->flags->C += 1;
	}
	else if (ft_strncmp("WE ", input, 3) == 0)
	{
		if (configs->texture->flags->WE == 0)
			configs->texture->w_texture = ft_strdup(rm_spaces(input + 2));
		configs->texture->flags->WE += 1;
	}
	else
		return (0);
	return (1);
}

int	check_lines2(char *input, t_configs *configs)
{
	if (ft_strncmp("EA ", input, 3) == 0)
	{
		if (configs->texture->flags->EA == 0)
			configs->texture->e_texture = ft_strdup(rm_spaces(input + 2));
		configs->texture->flags->EA += 1;
	}
	else if (ft_strncmp("F ", input, 2) == 0)
	{
		if (configs->texture->flags->F == 0)
			configs->texture->floor_c = ft_strdup(rm_spaces(input + 2));
		configs->texture->flags->F += 1;
	}
	else
		return (check_lines3(input, configs));
	return (1);
}

int	check_lines(char **f, t_configs *configs, int i)
{
	while (f[++i])
	{
		if (ft_strncmp("NO ", f[i], 3) == 0)
		{
			if (configs->texture->flags->NO == 0)
				configs->texture->n_texture = ft_strdup(rm_spaces(f[i] + 2));
			configs->texture->flags->NO += 1;
		}
		else if (ft_strncmp("SO ", f[i], 3) == 0)
		{
			if (configs->texture->flags->SO == 0)
				configs->texture->s_texture = ft_strdup(rm_spaces(f[i] + 2));
			configs->texture->flags->SO += 1;
		}
		else
		{
			if (!check_lines2(f[i], configs))
				return (error_message(f, 0), 0);
		}
	}
	if (configs->texture->flags->WE != 1 || configs->texture->flags->SO != 1
		|| configs->texture->flags->NO != 1 || configs->texture->flags->EA != 1 
		|| configs->texture->flags->F != 1 || configs->texture->flags->C != 1)
		return (error_message(f, 0), 0);
	return (error_message(f, 0), 1);
}
