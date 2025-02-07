/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:13:09 by noel-baz          #+#    #+#             */
/*   Updated: 2024/11/04 16:14:30 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lensrc;
	size_t	lendst;
	size_t	i;

	lensrc = ft_strlen(src);
	if (!dst && !dstsize)
		return (lensrc);
	i = 0;
	lendst = ft_strlen(dst);
	if (dstsize <= lendst)
		return (dstsize + lensrc);
	while (src[i] && i + lendst < dstsize - 1)
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lensrc + lendst);
}
