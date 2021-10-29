/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:18:53 by vleida            #+#    #+#             */
/*   Updated: 2021/04/22 13:17:28 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *has, const char *ned, size_t len)
{
	size_t	i;
	size_t	j;

	if (ned[0] == 0)
		return ((char *)has);
	i = 0;
	while (has[i] && i < len)
	{
		j = 0;
		while (has[i + j] && ned[j] && has[i + j] == ned[j] && (i + j) < len)
			j++;
		if (!ned[j])
			return (&((char *)has)[i]);
		i++;
	}
	return (NULL);
}
