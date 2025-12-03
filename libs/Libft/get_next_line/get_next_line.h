/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasbayou <hasbayou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:15:35 by amsbai            #+#    #+#             */
/*   Updated: 2025/12/02 10:25:01 by hasbayou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

char	*get_next_line(int fd);
char	*tabs_to_spaces(const char *str, int i, int j);
char	*ft_strjoin_2(char *s1, char *s2);

#endif
