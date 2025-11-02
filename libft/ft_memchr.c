/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:49:09 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/14 16:02:48 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	b;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	b = (unsigned char) c;
	while (i < n)
	{
		if (str[i] == b)
		{
			return ((void *) &str[i]);
		}
		i++;
	}
	return (NULL);
}
