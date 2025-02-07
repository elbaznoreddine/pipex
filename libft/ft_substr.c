/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:49:55 by noel-baz          #+#    #+#             */
/*   Updated: 2024/11/14 10:10:19 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_src;
	char	*substr;

	if (!s)
		return (NULL);
	len_src = ft_strlen(s);
	if (start > len_src)
		return (ft_strdup(""));
	if (len > len_src - start)
		len = len_src - start;
	substr = malloc(len + 1);
	if (substr == NULL)
		return (0);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}
