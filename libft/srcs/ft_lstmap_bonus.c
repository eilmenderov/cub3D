/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:10:01 by vleida            #+#    #+#             */
/*   Updated: 2021/04/21 20:14:28 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*buf;
	t_list	*start;
	t_list	*newl;

	if (!lst)
		return (NULL);
	buf = lst;
	start = ft_lstnew(f(buf->content));
	if (!start)
		return (NULL);
	buf = buf->next;
	while (buf)
	{
		newl = ft_lstnew(f(buf->content));
		if (!newl)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, newl);
		buf = buf->next;
	}
	return (start);
}
