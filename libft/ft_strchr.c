/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:35:27 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/13 18:26:25 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	d;

	d = c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return ((char *)&s[i]);
		i++;
	}
	if (d == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
