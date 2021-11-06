/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:59:45 by vleida            #+#    #+#             */
/*   Updated: 2021/11/01 18:23:58 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_skip_fw(char *str, unsigned char sym)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] == sym)
		i++;
	while (str[i] && str[i] != sym)
		i++;
	while (str[i] && str[i] == sym)
		i++;
	return (i);
}

char	*ft_first_word(char *line, unsigned char sym)
{
	int		len;
	int		i;
	int		j;

	len = ft_strlen_m(line, 0);
	if (!len)
		return (NULL);
	i = 0;
	while (line[i] && line[i] == sym)
		i++;
	j = i;
	while (line[j] && line[j] != sym)
		j++;
	if (i != j)
		return (ft_strndup(&line[i], j - i));
	return (NULL);
}

void	ft_free_all_lst(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
			free (tmp->content);
		tmp->content = NULL;
		tmp = tmp->next;
		free(lst);
		lst = tmp;
	}
}
