/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:25:13 by vleida            #+#    #+#             */
/*   Updated: 2021/04/22 13:13:10 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	num;
	size_t	i;
	char	*rez;

	if (!s)
		return (NULL);
	num = ft_strlen(s);
	rez = malloc(sizeof(char) * (num + 1));
	if (!rez)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rez[i] = f(i, s[i]);
		i++;
	}
	rez[i] = 0;
	return (rez);
}
