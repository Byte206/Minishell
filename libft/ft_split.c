/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:43:07 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/19 16:35:19 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;
	int		flag;

	count = 0;
	while (*s)
	{
		flag = 0;
		while (*s && *s == c)
			++s;
		while (*s && *s != c)
		{
			if (flag == 0)
			{
				count++;
				flag = 1701;
			}
			++s;
		}
	}
	return (count);
}

static int	check_malloc(char	**new, int i, size_t len)
{
	int	j;

	j = 0;
	new[i] = malloc(len);
	if (new[i] == NULL)
	{
		while (j < i)
			free(new[j++]);
		free(new);
		return (1);
	}
	return (0);
}

static int	complete(char	**new, const char *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
			++s;
		while (*s && *s != c)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (check_malloc(new, i, len + 1))
				return (1);
			ft_strlcpy(new[i], s - len, len + 1);
		}
		++i;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**new;

	if (NULL == s)
		return (NULL);
	words = word_count(s, c);
	new = malloc((words + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	new[words] = NULL;
	if (complete(new, s, c))
	{
		return (NULL);
	}
	return (new);
}
