/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:46:08 by amsbai            #+#    #+#             */
/*   Updated: 2025/09/09 17:13:31 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoinN(char *s1, char *s2)
{
	size_t	size;
	size_t	s1_len;
	size_t	s2_len;
	char	*s;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	size = s1_len + s2_len + 1;
	s = malloc(sizeof(char) * size);
	if (!s)
		return (0);
	s[size - 1] = 0;
	ft_memcpy(s, s1, s1_len);
	ft_memcpy(s + s1_len, s2, s2_len);
	return (s);
}

static int	strlen_tabs(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	return (len);
}

char	*tabs_to_spaces(const char *str, int i, int j)
{
	int tabs, len;
	char *res;

	if (!str)
		return (NULL);
	len = strlen_tabs((char *)str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\t')
		{
			tabs = 0;
			while (tabs < 4)
			{
				res[j++] = ' ';
				tabs++;
			}
		}
		else
			res[j++] = str[i];
		i++;
	}
	return ((res[j] = '\0'),res);
}
