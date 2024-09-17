// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:38:11 by lvez-dia          #+#    #+#             */
/*   Updated: 2024/05/16 10:28:23 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*buff;
	unsigned char	char_to_find;

	char_to_find = (unsigned char)c;
	buff = (unsigned char *)s;
	while (*buff)
	{
		if (*buff == char_to_find)
			return ((char *)buff);
		buff++;
	}
	if (*buff == char_to_find)
		return ((char *)buff);
	return (NULL);
}

static void	copy_strings(char *dst, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1 && s1[j])
		dst[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*return_str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = 0;
	len_s2 = 0;
	if (s1)
		len_s1 = ft_strlen(s1);
	if (s2)
		len_s2 = ft_strlen(s2);
	return_str = malloc(len_s1 + len_s2 + 1);
	if (!return_str)
		return (free(s1), NULL);
	copy_strings(return_str, s1, s2);
	free(s1);
	return (return_str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
