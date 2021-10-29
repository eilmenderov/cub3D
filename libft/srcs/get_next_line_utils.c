/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:48:24 by vleida            #+#    #+#             */
/*   Updated: 2021/10/06 16:23:15 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_gnl_cheker(char *ost)
{
	int	i;

	if (!ost)
		return (1);
	i = 0;
	while (*(ost + i) && *(ost + i) != '\n')
		i++;
	if (*(ost + i) == '\n')
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		answ;

	line = NULL;
	answ = ft_gnl_old(fd, &line);
	if (answ == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}
	if (line && answ)
		return (ft_strjoin(line, "\n"));
	if (line && line[0])
		return (line);
	if (line)
		free(line);
	return (NULL);
}
