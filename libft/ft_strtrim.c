/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:54:18 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/21 13:24:42 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	str;
	size_t	end;
	char	*new;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	new = 0;
	if (s1[0] != '\0' || set[0] != '\0')
	{
		str = 0;
		end = ft_strlen(s1);
		while (s1[str] && ft_strchr(set, s1[str]))
		{
			str++;
		}
		while (s1[end - 1] && ft_strchr(set, s1[end -1]) && end > str)
		{
			end--;
		}
		new = (char *)malloc(sizeof(char) * (end - str + 1));
		if (!new)
			return (NULL);
		ft_strlcpy(new, &s1[str], end - str + 1);
	}
	return (new);
}
