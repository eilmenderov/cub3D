/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:56:33 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 13:09:45 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

void	puterror(char *errorline)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(errorline, 1);
	exit(1);
}

void	ft_plane(t_player *player)
{
	player->plane.x = -player->dir.y * player->opt->cnst->tan_plane;
	player->plane.y = player->dir.x * player->opt->cnst->tan_plane;
}

double	ft_angle(t_player *plr)
{
	if (plr->angle <= 0)
		plr->angle += M_2PI;
	if (plr->angle > M_2PI)
		plr->angle -= M_2PI;
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
	while (*str && *str >= '0' && *str <= '9' && res <= 255)
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	if ((res > 255 && negative == 1) || (*str != ',' && *str != 0))
		puterror("incorrect color format(atoi_m 2)");
	return ((int)res * negative);
}
