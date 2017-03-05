/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:38:31 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/03 03:00:14 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING__H
# define STRING__H

# include <stddef.h>

size_t	strlen_(const char *s);
char	*strchr_(const char *s, int c);
char	*strchr_i(const char *s, int c, int *index);
char	*strnchr_(const char *s, int c, size_t n);
size_t	strnlen_(const char *s, size_t n);
int		strcmp_(const char *s1, const char *s2);
int		strncmp_(const char *s1, const char *s2, size_t n);
char	*strcpy_(char *s1, const char *s2);
char	*strcat_(char *s1, const char *s2);
char	*strdup_(const char *s);
char	*strnew_(size_t size);
void	bzero_(void *s, size_t n);
void	*memset_(void *str, int c, size_t n);
char	*strjoin_(char const *s1, char const *s2);

#endif
