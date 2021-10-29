/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:13:44 by vleida            #+#    #+#             */
/*   Updated: 2021/04/21 17:55:09 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_end;

	if (lst)
	{
		if (*lst)
		{
			lst_end = ft_lstlast(*lst);
			lst_end->next = new;
		}
		else
			*lst = new;
	}
}
