/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:08:56 by vleida            #+#    #+#             */
/*   Updated: 2021/04/21 10:27:09 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*rez;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	rez = malloc(sizeof(char) * len + 1);
	if (!rez)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		rez[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		rez[i] = *s2;
		i++;
		s2++;
	}
	rez[i] = 0;
	return (rez);
}
