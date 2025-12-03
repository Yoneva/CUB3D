/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:52:28 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/02 11:36:39 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_lines3(char *input, t_configs *configs)
{
	if (ft_strncmp("C ", input, 2) == 0)
	{
		if (configs->texture->flags->c == 0)
			configs->texture->ceiling_c = rm_spaces(input + 2);
		configs->texture->flags->c += 1;
	}
	else if (ft_strncmp("WE ", input, 3) == 0)
	{
		if (configs->texture->flags->we == 0)
			configs->texture->w_texture = rm_spaces(input + 2);
		configs->texture->flags->we += 1;
	}
	else
		return (0);
	return (1);
}

int	check_lines2(char *input, t_configs *configs)
{
	if (ft_strncmp("EA ", input, 3) == 0)
	{
		if (configs->texture->flags->ea == 0)
			configs->texture->e_texture = rm_spaces(input + 2);
		configs->texture->flags->ea += 1;
	}
	else if (ft_strncmp("F ", input, 2) == 0)
	{
		if (configs->texture->flags->f == 0)
			configs->texture->floor_c = rm_spaces(input + 2);
		configs->texture->flags->f += 1;
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
			if (configs->texture->flags->no == 0)
				configs->texture->n_texture = rm_spaces(f[i] + 2);
			configs->texture->flags->no += 1;
		}
		else if (ft_strncmp("SO ", f[i], 3) == 0)
		{
			if (configs->texture->flags->so == 0)
				configs->texture->s_texture = rm_spaces(f[i] + 2);
			configs->texture->flags->so += 1;
		}
		else
		{
			if (!check_lines2(f[i], configs))
				return (error_message(f, 0), 0);
		}
	}
	if (configs->texture->flags->we != 1 || configs->texture->flags->so != 1
		|| configs->texture->flags->no != 1 || configs->texture->flags->ea != 1 
		|| configs->texture->flags->f != 1 || configs->texture->flags->c != 1)
		return (error_message(f, 0), 0);
	return (error_message(f, 0), 1);
}
