#include "head_cub.h"

void	my_mlx_pixel_put(t_opt *opt, int x, int y, int color)
{
	char	*dst;

	dst = opt->mand->addr + (y * opt->mand->line_length + x
			* (opt->mand->b_p_p / 8));
	*(unsigned int *)dst = color;
}

void	ft_cast_one_ray(t_opt *opt, int diff)
{
	float	x;
	float	y;
	float	l;
	float	full_angle;

	full_angle = opt->plr->angle * 0.5;
	x = opt->plr->pos_x - diff / 2;
	y = opt->plr->pos_y - diff / 2;
	while (opt->map->canvas[(int)(y / PIC_SIZE)][(int)(x / PIC_SIZE)] != '1')
	{
		x += cos(full_angle);
		y += sin(full_angle);
		my_mlx_pixel_put(opt, (int)x, (int)y, 0x990099);
	}
	l = sqrt(pow(opt->plr->pos_x - x, 2) + pow(opt->plr->pos_y - y, 2));
}

void	ft_cast_rays(t_opt *opt, int diff)
{
	float	x;
	float	y;
	float	start;
	float	end;

	opt->plr->angle = ft_angle(opt->plr->angle);
	start = opt->plr->angle;
	end = start + ANGLE;
	while (start < end)
	{
		x = opt->plr->pos_x * MAP_SIZE - diff / 2;
		y = opt->plr->pos_y * MAP_SIZE - diff / 2;
		while (opt->map->canvas[(int)(y / MAP_SIZE)][(int)(x / MAP_SIZE)] != '1')
		{
			x += cos(start - ANGLE * 0.5);
			y += sin(start - ANGLE * 0.5);
			my_mlx_pixel_put(opt, (int)x, (int)y, 0x990099);
		}
		start += (ANGLE / REYS);
	}
}

void	sizepixel_player(t_opt *opt, int x, int y, int color)
{
	int	x_size;
	int	y_size;
	int	diff;

	diff = MAP_SIZE - (int)(MAP_SIZE * 0.8);
	// ft_cast_one_ray(opt, diff);
	ft_cast_rays(opt, diff);
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

void	sizepixel(t_opt *opt, int x, int y, int color)
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
				sizepixel(opt, step_x, step_y, 0xFFFFFF);
			else if (ft_ch_for_coinc(opt->map->canvas[y][x], "0NSEW"))
			{
				sizepixel(opt, step_x, step_y, 0x708090);
				if (ft_ch_for_coinc(opt->map->canvas[y][x], HERO))
				{
					opt->map->viewpos = opt->map->canvas[y][x];
					opt->map->canvas[y][x] = '0';
				}
			}
			step_x += MAP_SIZE;
		}
		step_y += MAP_SIZE;
	}
	sizepixel_player(opt, (int)(opt->plr->pos_x * MAP_SIZE), (int)(opt->plr->pos_y * MAP_SIZE), 0xFF0000);
}
