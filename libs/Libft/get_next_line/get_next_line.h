/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsbai <amsbai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:15:35 by amsbai            #+#    #+#             */
/*   Updated: 2025/11/30 17:27:48 by amsbai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include "../libft.h"
# include <stdlib.h>

char	*get_next_line(int fd);
char	*tabs_to_spaces(const char *str, int i, int j);
char	*ft_strjoinN(char *s1, char *s2);

#endif