/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:50:59 by vleida            #+#    #+#             */
/*   Updated: 2021/04/21 13:24:18 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_razm(int c)
{
	int	result;

	result = 0;
	if (c < 0)
		result++;
	while (c / 10)
	{
		c = c / 10;
		result++;
	}
	return (result + 1);
}

static void	ft_str_nbr(int nb, int razm, char *rez)
{
	if (nb == -2147483648)
	{
		ft_str_nbr(nb / 10, razm - 1, rez);
		rez[razm - 1] = 56;
	}
	else if (nb < 0)
	{
		rez[0] = 45;
		ft_str_nbr(-nb, razm, rez);
	}
	else
	{
		if (nb / 10)
			ft_str_nbr(nb / 10, razm - 1, rez);
		rez[razm - 1] = nb % 10 + 48;
	}
}

char	*ft_itoa(int n)
{
	int		razm;
	char	*rez;

	razm = ft_razm(n);
	rez = malloc(sizeof(char) * (razm + 1));
	if (!rez)
		return (NULL);
	rez[razm] = 0;
	ft_str_nbr(n, razm, rez);
	return (rez);
}
