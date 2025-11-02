/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:29:01 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/21 13:07:01 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		s_len;
	char	ocurr ;

	ocurr = c;
	s_len = ft_strlen(s);
	if (ocurr == '\0')
		return ((char *)&s[s_len]);
	while (s_len >= 0)
	{
		if (s[s_len] == ocurr)
			return ((char *)&s[s_len]);
		s_len--;
	}
	return (NULL);
}
