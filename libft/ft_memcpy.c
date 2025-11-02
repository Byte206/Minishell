/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:59:03 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/13 16:20:38 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned const char		*o;
	unsigned char			*f;
	size_t					i;

	i = 0;
	o = (unsigned char *)src;
	f = (unsigned char *)dest;
	if (dest == src || n <= 0)
	{
		return (dest);
	}
	while (i < n)
	{
		f[i] = o[i];
		i++;
	}
	return (dest);
}
