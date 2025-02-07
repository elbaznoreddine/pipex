/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:17:35 by noel-baz          #+#    #+#             */
/*   Updated: 2025/01/11 05:10:12 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_(char *s)
{
	char	*str;
	int		i;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen_(s);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup_(s2));
	str = malloc(ft_strlen_(s1) + ft_strlen_(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr_(char *s, unsigned int index, size_t bytes)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (index > ft_strlen_(s))
		return (ft_strdup_(""));
	if (bytes > ft_strlen_(s) - index)
		bytes = ft_strlen_(s) - index;
	str = malloc(bytes + 1);
	if (!str)
		return (NULL);
	while (bytes--)
	{
		str[i++] = s[index++];
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr_(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
