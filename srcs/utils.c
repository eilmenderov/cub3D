/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:56:33 by vleida            #+#    #+#             */
/*   Updated: 2021/11/05 17:49:22 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_cub.h"

void	puterror(char *errorline)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(errorline, 1);
	exit(1);
}

float	ft_angle(float alpha)
{
	if (alpha <= 0)
		alpha += M_PI * 2;
	if (alpha > M_PI * 2)
		alpha -= M_PI * 2;
	return (alpha);
}
