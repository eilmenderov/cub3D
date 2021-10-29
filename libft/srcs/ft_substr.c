/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:53:00 by vleida            #+#    #+#             */
/*   Updated: 2021/10/06 13:21:12 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*rez;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (i < len)
		len = i;
	rez = malloc(sizeof(char) * len + 1);
	if (!rez)
		return (NULL);
	rez[0] = 0;
	if (i <= start)
		return (rez);
	i = 0;
	while (start + i < start + len)
	{
		rez[i] = s[start + i];
		i++;
	}
	rez[i] = 0;
	return (rez);
}
