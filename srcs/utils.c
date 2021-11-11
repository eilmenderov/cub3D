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

double	ft_angle(t_player *plr)
{

	// alpha = atan(plr->plane.y / plr->plane.x);
	// alpha = plr->angle;
	// printf("angle: %f p_x: %f p_y: %f\n", alpha, plr->plane.x, plr->plane.y);
	if (plr->angle <= 0)
		plr->angle += M_PI * 2;
	if (plr->angle > M_PI * 2)
		plr->angle -= M_PI * 2;
	return (plr->angle);
}

int	ft_atoi_m(const char *str)
{
	int					negative;
	unsigned long long	res;

	negative = 1;
	res = 0;
	while (*str && (*str == 32 || (*str > 8 && *str < 14)))
		str++;
	if (*str == '-')
		puterror("incorrect color format(atoi_m 1)");
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9' && res <= FT_ATOI_MN)
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	if ((res > FT_ATOI_MV && negative == 1) || (*str != ',' && *str != 0))
		puterror("incorrect color format(atoi_m 2)");
	return ((int)res * negative);
}
