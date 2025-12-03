/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:02:21 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/02 11:36:28 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
