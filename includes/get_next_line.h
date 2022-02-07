/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:02:34 by ncarob            #+#    #+#             */
/*   Updated: 2021/10/18 22:57:30 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096

# endif /* BUFFER_SIZE */

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*add_buffer(char const *s1, char const *s2);

#endif /* GET_NEXT_LINE_H */