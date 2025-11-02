/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:23:49 by gamorcil          #+#    #+#             */
/*   Updated: 2025/01/19 16:34:35 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_num(long int nbr)
{
	int	size;

	size = 0;
	if (nbr < 0)
	{
		size++;
		nbr *= -1;
	}
	if (nbr == 0)
		size++;
	while (nbr != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

static char	*convert_str(char	*new, long int nbr, int n, int size)
{
	int	i;

	i = size - 1;
	if (n < 0)
	{
		new[0] = '-';
		nbr *= -1;
	}
	while (nbr != 0)
	{
		new[i] = ((nbr % 10) + '0');
		nbr /= 10;
		i--;
	}
	new[size] = '\0';
	return (new);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	char		*new;
	int			size;

	nbr = n;
	size = count_num(nbr);
	new = (char *)malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '0';
	new = convert_str(new, nbr, n, size);
	return (new);
}
