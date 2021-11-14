/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:50:10 by vleida            #+#    #+#             */
/*   Updated: 2021/11/14 11:50:11 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_cub.h"

static void	ft_cast_rays(t_opt *opt, double x, double y)
{
	double	x_s;
	double	y_s;
	double	start;
	double	end;
	double	step;

	start = ft_angle(opt->plr);
	end = start + opt->cnst->angle;
	step = opt->cnst->map_step;
	while (start < end)
	{
		x_s = x;
		y_s = y;
		while (opt->map->canvas[(int)(y_s / MAP_SIZE)][(int)(x_s / MAP_SIZE)]
			!= '1')
		{
			x_s += cos(start - opt->cnst->half_angle);
			y_s += sin(start - opt->cnst->half_angle);
			my_mlx_pixel_put(opt, (int)x_s, (int)y_s, MAP_RAY_COLOR);
		}
		start += step;
	}
}

static void	sizepixel_player(t_opt *opt, int x, int y, int color)
{
	int		x_size;
	int		y_size;
	double	diff;

	diff = opt->cnst->map_diff;
	ft_cast_rays(opt, x, y);
	y = y + diff;
	x = x + diff;
	y_size = y - diff;
	while (y_size < y && y_size < RES_Y)
	{
		x_size = x - diff;
		while (x_size < x && x_size < RES_X)
		{
			my_mlx_pixel_put(opt, x_size, y_size, color);
			x_size++;
		}
		y_size++;
	}
}

static void	sizepixel(t_opt *opt, int x, int y, int color)
{
	int	x_size;
	int	y_size;

	y_size = y;
	while (y_size < y + MAP_SIZE && y_size < RES_Y)
	{
		x_size = x;
		while (x_size < x + MAP_SIZE && x_size < RES_X)
		{
			my_mlx_pixel_put(opt, x_size, y_size, color);
			x_size++;
		}
		y_size++;
	}
}

void	print_minimap(t_opt *opt)
{
	int	x;
	int	y;	
	int	step_x;
	int	step_y;

	y = -1;
	step_y = 0;
	while (opt->map->canvas[++y])
	{
		step_x = 0;
		x = -1;
		while (opt->map->canvas[y][++x])
		{
			if (opt->map->canvas[y][x] == '1')
				sizepixel(opt, step_x, step_y, MAP_W_COLOR);
			step_x += MAP_SIZE;
		}
		step_y += MAP_SIZE;
	}
	sizepixel_player(opt, (int)(opt->plr->pos.x * MAP_SIZE),
		(int)(opt->plr->pos.y * MAP_SIZE), MAP_PL_COLOR);
}
