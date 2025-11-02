/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:17:08 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/14 17:25:57 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s) + 1;
	new = (char *)malloc(size);
	if (!new)
		return (NULL);
	size = 0;
	while (s[size] != '\0')
	{
		new[size] = s[size];
		size++;
	}
	new[size] = '\0';
	return (new);
}
