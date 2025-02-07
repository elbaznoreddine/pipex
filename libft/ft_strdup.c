/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:48:01 by noel-baz          #+#    #+#             */
/*   Updated: 2024/11/07 11:38:20 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	slen;

	slen = ft_strlen(s1);
	ptr = malloc(slen + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[slen] = '\0';
	return (ft_memmove(ptr, s1, slen));
}
