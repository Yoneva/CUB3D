/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:02:45 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/30 17:03:09 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/parsing.h"

int	count_word(char *input)
{
	int	i;
	int	count;
	int	find;

	i = 0;
	count = 0;
	find = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\t' || input[i] == 32)
		{
			find = 0;
		}
		else if (input[i] != '\t' && input[i] != 32)
		{
			if (find == 0)
			{
				count++;
				find = 1;
			}
		}
		i++;
	}
	return (count);
}
