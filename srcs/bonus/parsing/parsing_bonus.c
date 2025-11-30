/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:13:09 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/30 18:02:00 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	error_message(char **arr, int n)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free (arr[i]);
		i++;
	}
	free (arr);
	if (n == 1)
	{
		write(1, "Error!\n", 7);
		exit (1);
	}
}

char	**get_file(int fd)
{
	int		i;
	int		len;
	int		size;
	char	**arr;

	i = 0;
	size = 1;
	arr = malloc(size * sizeof(char *));
	while (1)
	{
		arr[i] = get_next_line(fd);
		if (!arr[i])
			break ;
		len = ft_strlen(arr[i]);
		if (arr[i][len - 1] == '\n')
			arr[i][len - 1] = '\0';
		size += 1;
		arr = ft_realloc(arr, (size * sizeof(char *)));
		i++;
	}
	return (arr);
}
