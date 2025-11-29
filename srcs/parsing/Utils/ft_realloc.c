/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:37:24 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/18 05:21:03 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"


void	*ft_realloc(void *str, size_t newsize)
{
	char	**newptr;

	if (str == 0)
		return (malloc(newsize));
	if (newsize == 0)
	{
		free (str);
		return (NULL);
	}
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	ft_memmove(newptr, str, newsize);
	free(str);
	return (newptr);
}
