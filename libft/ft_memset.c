/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:37:15 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/13 15:50:50 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int a, size_t n)
{
	size_t			x;
	unsigned char	*str2;

	str2 = str;
	x = 0;
	while (x < n)
	{
		str2[x] = a;
		x++;
	}
	return (str);
}
